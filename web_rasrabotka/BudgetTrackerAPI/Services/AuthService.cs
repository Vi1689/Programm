using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using BudgetAPI.Data;
using BudgetAPI.Models;
using BudgetAPI.Models.DTOs;

namespace BudgetAPI.Services
{
    public class AuthService
    {
        private readonly AppDbContext _db;
        private readonly IConfiguration _config;
        private readonly PasswordHasher<User> _passwordHasher;

        public AuthService(AppDbContext db, IConfiguration config)
        {
            _db = db;
            _config = config;
            _passwordHasher = new PasswordHasher<User>();
        }

        public async Task<(bool Success, string? Error, AuthResponseDto? Response)> RegisterAsync(RegisterDto dto)
        {
            // Check if email already exists
            if (await _db.Users.AnyAsync(u => u.Email == dto.Email))
            {
                return (false, "Email уже используется", null);
            }

            // Check if username already exists
            if (await _db.Users.AnyAsync(u => u.Username == dto.Username))
            {
                return (false, "Имя пользователя уже используется", null);
            }

            var user = new User
            {
                Email = dto.Email,
                Username = dto.Username,
                Role = "User",
                CreatedAt = DateTime.UtcNow
            };

            // Hash password
            user.PasswordHash = _passwordHasher.HashPassword(user, dto.Password);

            _db.Users.Add(user);
            await _db.SaveChangesAsync();

            var token = GenerateJwtToken(user);

            return (true, null, new AuthResponseDto
            {
                Token = token,
                UserId = user.Id,
                Email = user.Email,
                Username = user.Username,
                Role = user.Role
            });
        }

        public async Task<(bool Success, string? Error, AuthResponseDto? Response)> LoginAsync(LoginDto dto)
        {
            var user = await _db.Users.FirstOrDefaultAsync(u => u.Email == dto.Email);
            
            if (user == null)
            {
                return (false, "Неверный email или пароль", null);
            }

            // Verify password
            var result = _passwordHasher.VerifyHashedPassword(user, user.PasswordHash, dto.Password);
            
            if (result == PasswordVerificationResult.Failed)
            {
                return (false, "Неверный email или пароль", null);
            }

            var token = GenerateJwtToken(user);

            return (true, null, new AuthResponseDto
            {
                Token = token,
                UserId = user.Id,
                Email = user.Email,
                Username = user.Username,
                Role = user.Role
            });
        }

        private string GenerateJwtToken(User user)
        {
            var key = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(_config["Jwt:Key"] ?? "SuperSecretKeyForBudgetApp2024"));
            var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);

            var claims = new[]
            {
                new Claim(ClaimTypes.NameIdentifier, user.Id.ToString()),
                new Claim(ClaimTypes.Email, user.Email),
                new Claim(ClaimTypes.Name, user.Username),
                new Claim(ClaimTypes.Role, user.Role)
            };

            var token = new JwtSecurityToken(
                issuer: _config["Jwt:Issuer"] ?? "BudgetAPI",
                audience: _config["Jwt:Audience"] ?? "BudgetClient",
                claims: claims,
                expires: DateTime.UtcNow.AddDays(7),
                signingCredentials: creds
            );

            return new JwtSecurityTokenHandler().WriteToken(token);
        }
    }
}
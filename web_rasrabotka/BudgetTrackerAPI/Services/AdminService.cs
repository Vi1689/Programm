using Microsoft.EntityFrameworkCore;
using BudgetAPI.Data;
using BudgetAPI.Models;

namespace BudgetAPI.Services
{
    public class AdminService
    {
        private readonly AppDbContext _db;
        
        public AdminService(AppDbContext db)
        {
            _db = db;
        }
        
        public async Task<List<UserDto>> GetAllUsersAsync()
        {
            return await _db.Users
                .Select(u => new UserDto
                {
                    Id = u.Id,
                    Email = u.Email,
                    Username = u.Username,
                    Role = u.Role,
                    CreatedAt = u.CreatedAt,
                    TransactionsCount = u.Transactions.Count
                })
                .OrderBy(u => u.Id)
                .ToListAsync();
        }
        
        public async Task<User?> GetUserByIdAsync(int id)
        {
            return await _db.Users
                .Include(u => u.Transactions)
                .FirstOrDefaultAsync(u => u.Id == id);
        }
        
        public async Task<bool> DeleteUserAsync(int id)
        {
            var user = await _db.Users.FindAsync(id);
            if (user == null) return false;
            
            if (user.Role == "Admin")
            {
                throw new InvalidOperationException("Нельзя удалить администратора");
            }
            
            _db.Users.Remove(user);
            await _db.SaveChangesAsync();
            return true;
        }
        
        public async Task<bool> UpdateUserRoleAsync(int id, string role)
        {
            var user = await _db.Users.FindAsync(id);
            if (user == null) return false;
            
            if (role != "User" && role != "Admin")
            {
                throw new ArgumentException("Роль должна быть 'User' или 'Admin'");
            }
            
            user.Role = role;
            _db.Users.Update(user);
            await _db.SaveChangesAsync();
            return true;
        }
        
        public async Task<AdminStatsDto> GetAdminStatsAsync()
        {
            var totalUsers = await _db.Users.CountAsync();
            var totalTransactions = await _db.Transactions.CountAsync();
            
            var allTransactions = await _db.Transactions.ToListAsync();
            
            var totalIncome = allTransactions
                .Where(t => t.IsIncome)
                .Sum(t => t.Amount);
            
            var totalExpense = allTransactions
                .Where(t => !t.IsIncome)
                .Sum(t => t.Amount);
            
            var recentTransactions = await _db.Transactions
                .Include(t => t.User)
                .OrderByDescending(t => t.Date)
                .Take(10)
                .Select(t => new TransactionSimpleDto
                {
                    Id = t.Id,
                    Amount = t.Amount,
                    Category = t.Category,
                    Description = t.Description,
                    Date = t.Date,
                    IsIncome = t.IsIncome,
                    UserId = t.UserId,
                    Username = t.User != null ? t.User.Username : ""
                })
                .ToListAsync();
            
            return new AdminStatsDto
            {
                TotalUsers = totalUsers,
                TotalTransactions = totalTransactions,
                TotalIncome = totalIncome,
                TotalExpense = totalExpense,
                RecentTransactions = recentTransactions
            };
        }
    }
    
    public class AdminStatsDto
    {
        public int TotalUsers { get; set; }
        public int TotalTransactions { get; set; }
        public decimal TotalIncome { get; set; }
        public decimal TotalExpense { get; set; }
        public List<TransactionSimpleDto> RecentTransactions { get; set; } = new();
    }
    
    public class TransactionSimpleDto
    {
        public int Id { get; set; }
        public decimal Amount { get; set; }
        public string Category { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public DateTime Date { get; set; }
        public bool IsIncome { get; set; }
        public int UserId { get; set; }
        public string Username { get; set; } = string.Empty;
    }
    
    public class UserDto
    {
        public int Id { get; set; }
        public string Email { get; set; } = string.Empty;
        public string Username { get; set; } = string.Empty;
        public string Role { get; set; } = string.Empty;
        public DateTime CreatedAt { get; set; }
        public int TransactionsCount { get; set; }
    }
}
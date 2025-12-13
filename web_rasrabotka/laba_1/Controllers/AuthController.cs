using Microsoft.AspNetCore.Mvc;
using ValeraAPI.Models.DTOs;
using ValeraAPI.Services;

namespace ValeraAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class AuthController : ControllerBase
    {
        private readonly AuthService _authService;

        public AuthController(AuthService authService)
        {
            _authService = authService;
        }

        [HttpPost("register")]
        public async Task<IActionResult> Register([FromBody] RegisterDto dto)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            var (success, error, response) = await _authService.RegisterAsync(dto);

            if (!success)
            {
                return BadRequest(new { message = error });
            }

            return Ok(response);
        }

        [HttpPost("login")]
        public async Task<IActionResult> Login([FromBody] LoginDto dto)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            var (success, error, response) = await _authService.LoginAsync(dto);

            if (!success)
            {
                return Unauthorized(new { message = error });
            }

            return Ok(response);
        }
    }
}
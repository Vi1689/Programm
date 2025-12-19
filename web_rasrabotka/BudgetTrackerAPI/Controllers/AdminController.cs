using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using BudgetAPI.Services;

namespace BudgetAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    [Authorize(Roles = "Admin")]
    public class AdminController : ControllerBase
    {
        private readonly AdminService _adminService;
        
        public AdminController(AdminService adminService)
        {
            _adminService = adminService;
        }
        
        [HttpGet("users")]
        public async Task<IActionResult> GetAllUsers()
        {
            var users = await _adminService.GetAllUsersAsync();
            return Ok(users);
        }
        
        [HttpGet("stats")]
        public async Task<IActionResult> GetAdminStats()
        {
            var stats = await _adminService.GetAdminStatsAsync();
            return Ok(stats);
        }
        
        [HttpPut("users/{id}/role")]
        public async Task<IActionResult> UpdateUserRole(int id, [FromBody] UpdateRoleDto dto)
        {
            try
            {
                var success = await _adminService.UpdateUserRoleAsync(id, dto.Role);
                if (!success) return NotFound();
                
                return Ok(new { message = "Роль пользователя обновлена" });
            }
            catch (ArgumentException ex)
            {
                return BadRequest(new { message = ex.Message });
            }
        }
        
        [HttpDelete("users/{id}")]
        public async Task<IActionResult> DeleteUser(int id)
        {
            try
            {
                var success = await _adminService.DeleteUserAsync(id);
                if (!success) return NotFound();
                
                return Ok(new { message = "Пользователь удален" });
            }
            catch (InvalidOperationException ex)
            {
                return BadRequest(new { message = ex.Message });
            }
        }
    }
    
    public class UpdateRoleDto
    {
        public string Role { get; set; } = string.Empty;
    }
}
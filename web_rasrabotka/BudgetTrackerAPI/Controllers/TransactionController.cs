using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using BudgetAPI.Models.DTOs;
using BudgetAPI.Services;

namespace BudgetAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    [Authorize]
    public class TransactionController : ControllerBase
    {
        private readonly TransactionService _transactionService;
        
        public TransactionController(TransactionService transactionService)
        {
            _transactionService = transactionService;
        }
        
        private int GetUserId() => int.Parse(User.FindFirst(ClaimTypes.NameIdentifier)?.Value ?? "0");
        private bool IsAdmin() => User.IsInRole("Admin");
        
        [HttpGet]
        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> GetAll(
            [FromQuery] DateTime? startDate,
            [FromQuery] DateTime? endDate)
        {
            var transactions = await _transactionService.GetAllTransactionsAsync(startDate, endDate);
            return Ok(transactions);
        }
        
        [HttpGet("my")]
        public async Task<IActionResult> GetMy(
            [FromQuery] DateTime? startDate,
            [FromQuery] DateTime? endDate)
        {
            var transactions = await _transactionService.GetMyTransactionsAsync(GetUserId(), startDate, endDate);
            return Ok(transactions);
        }
        
        [HttpGet("{id}")]
        public async Task<IActionResult> Get(int id)
        {
            var transaction = await _transactionService.GetByIdAsync(id);
            if (transaction == null) return NotFound();
            
            if (!IsAdmin() && transaction.UserId != GetUserId())
                return Forbid();
            
            return Ok(transaction);
        }
        
        [HttpGet("stats")]
        public async Task<IActionResult> GetStats(
            [FromQuery] DateTime? startDate,
            [FromQuery] DateTime? endDate)
        {
            var stats = await _transactionService.GetStatsAsync(GetUserId(), startDate, endDate);
            return Ok(stats);
        }
        
        [HttpPost]
        public async Task<IActionResult> Create([FromBody] TransactionCreateDto dto)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }
            
            try
            {
                var transaction = await _transactionService.CreateAsync(dto, GetUserId());
                return CreatedAtAction(nameof(Get), new { id = transaction.Id }, transaction);
            }
            catch (Exception ex)
            {
                return BadRequest(new { message = ex.Message });
            }
        }
        
        [HttpPut("{id}")]
        public async Task<IActionResult> Update(int id, [FromBody] TransactionUpdateDto dto)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }
            
            var success = await _transactionService.UpdateAsync(id, dto, GetUserId());
            if (!success) return NotFound();
            
            return Ok(new { message = "Транзакция обновлена" });
        }
        
        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            var success = await _transactionService.DeleteAsync(id, GetUserId());
            if (!success) return NotFound();
            
            return Ok(new { message = "Транзакция удалена" });
        }
    }
}
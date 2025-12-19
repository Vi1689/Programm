using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using BudgetAPI.Models.DTOs;
using BudgetAPI.Services;

namespace BudgetAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    [Authorize]
    public class CategoryController : ControllerBase
    {
        private readonly CategoryService _categoryService;
        
        public CategoryController(CategoryService categoryService)
        {
            _categoryService = categoryService;
        }
        
        [HttpGet]
        public async Task<IActionResult> GetAll()
        {
            var categories = await _categoryService.GetAllCategoriesAsync();
            return Ok(categories);
        }
        
        [HttpGet("type/{type}")]
        public async Task<IActionResult> GetByType(string type)
        {
            if (type != "Expense" && type != "Income")
            {
                return BadRequest(new { message = "Тип должен быть 'Expense' или 'Income'" });
            }
            
            var categories = await _categoryService.GetCategoriesByTypeAsync(type);
            return Ok(categories);
        }
        
        [HttpGet("popular")]
        public async Task<IActionResult> GetPopular([FromQuery] int limit = 8)
        {
            var categories = await _categoryService.GetPopularCategoriesAsync(limit);
            return Ok(categories);
        }
        
        [HttpPost]
        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> Create([FromBody] CategoryCreateDto dto)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }
            
            try
            {
                var category = await _categoryService.CreateCategoryAsync(dto);
                return CreatedAtAction(nameof(GetAll), null, category);
            }
            catch (InvalidOperationException ex)
            {
                return BadRequest(new { message = ex.Message });
            }
        }
        
        [HttpDelete("{id}")]
        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> Delete(int id)
        {
            try
            {
                var success = await _categoryService.DeleteCategoryAsync(id);
                if (!success) return NotFound();
                
                return Ok(new { message = "Категория удалена" });
            }
            catch (InvalidOperationException ex)
            {
                return BadRequest(new { message = ex.Message });
            }
        }
    }
}
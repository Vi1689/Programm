using Microsoft.EntityFrameworkCore;
using BudgetAPI.Data;
using BudgetAPI.Models;
using BudgetAPI.Models.DTOs;

namespace BudgetAPI.Services
{
    public class CategoryService
    {
        private readonly AppDbContext _db;
        
        public CategoryService(AppDbContext db)
        {
            _db = db;
        }
        
        public async Task<List<Category>> GetAllCategoriesAsync()
        {
            return await _db.Categories
                .OrderByDescending(c => c.UsageCount)
                .ThenBy(c => c.Name)
                .ToListAsync();
        }
        
        public async Task<List<Category>> GetCategoriesByTypeAsync(string type)
        {
            return await _db.Categories
                .Where(c => c.Type == type)
                .OrderByDescending(c => c.UsageCount)
                .ThenBy(c => c.Name)
                .ToListAsync();
        }
        
        public async Task<Category?> GetCategoryByIdAsync(int id)
        {
            return await _db.Categories.FindAsync(id);
        }
        
        public async Task<Category?> GetCategoryByNameAsync(string name)
        {
            return await _db.Categories
                .FirstOrDefaultAsync(c => c.Name == name);
        }
        
        public async Task<List<PopularCategoryDto>> GetPopularCategoriesAsync(int limit = 8)
        {
            return await _db.Categories
                .Where(c => c.UsageCount > 0)
                .OrderByDescending(c => c.UsageCount)
                .Take(limit)
                .Select(c => new PopularCategoryDto
                {
                    Name = c.Name,
                    Icon = c.Icon,
                    Color = c.Color,
                    Type = c.Type,
                    UsageCount = c.UsageCount
                })
                .ToListAsync();
        }
        
        public async Task<Category> CreateCategoryAsync(CategoryCreateDto dto)
        {
            // Check if category already exists
            var existingCategory = await GetCategoryByNameAsync(dto.Name);
            if (existingCategory != null)
            {
                throw new InvalidOperationException($"Категория '{dto.Name}' уже существует");
            }
            
            var category = new Category
            {
                Name = dto.Name,
                Icon = dto.Icon,
                Color = dto.Color,
                Type = dto.Type,
                IsSystem = false,
                UsageCount = 0,
                CreatedAt = DateTime.UtcNow
            };
            
            _db.Categories.Add(category);
            await _db.SaveChangesAsync();
            
            return category;
        }
        
        public async Task<bool> UpdateCategoryAsync(Category category)
        {
            _db.Categories.Update(category);
            await _db.SaveChangesAsync();
            return true;
        }
        
        public async Task<bool> DeleteCategoryAsync(int id)
        {
            var category = await _db.Categories.FindAsync(id);
            if (category == null) return false;
            
            // Can't delete system categories
            if (category.IsSystem)
            {
                throw new InvalidOperationException("Нельзя удалить системную категорию");
            }
            
            // Check if category is in use
            var isUsed = await _db.Transactions.AnyAsync(t => t.Category == category.Name);
            if (isUsed)
            {
                throw new InvalidOperationException("Нельзя удалить категорию, которая используется в транзакциях");
            }
            
            _db.Categories.Remove(category);
            await _db.SaveChangesAsync();
            return true;
        }
    }
}
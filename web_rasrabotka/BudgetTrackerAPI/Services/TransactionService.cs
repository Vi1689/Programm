using Microsoft.EntityFrameworkCore;
using BudgetAPI.Data;
using BudgetAPI.Models;
using BudgetAPI.Models.DTOs;

namespace BudgetAPI.Services
{
    public class TransactionService
    {
        private readonly AppDbContext _db;
        private readonly CategoryService _categoryService;
        
        public TransactionService(AppDbContext db, CategoryService categoryService)
        {
            _db = db;
            _categoryService = categoryService;
        }
        
        public async Task<List<TransactionResponseDto>> GetMyTransactionsAsync(int userId, DateTime? startDate = null, DateTime? endDate = null)
        {
            var query = _db.Transactions
                .Where(t => t.UserId == userId);
            
            if (startDate.HasValue)
                query = query.Where(t => t.Date >= startDate.Value);
            
            if (endDate.HasValue)
                query = query.Where(t => t.Date <= endDate.Value);
            
            var transactions = await query.OrderByDescending(t => t.Date).ToListAsync();
            
            return transactions.Select(t => new TransactionResponseDto
            {
                Id = t.Id,
                Amount = t.Amount,
                Category = t.Category,
                Description = t.Description,
                Date = t.Date,
                IsIncome = t.IsIncome,
                CategoryColor = t.CategoryColor,
                CategoryIcon = t.CategoryIcon,
                UserId = t.UserId,
                Username = "" // Можно добавить запрос к базе если нужно
            }).ToList();
        }
        
        public async Task<List<TransactionResponseDto>> GetAllTransactionsAsync(DateTime? startDate = null, DateTime? endDate = null)
        {
            var query = _db.Transactions.AsQueryable();
            
            if (startDate.HasValue)
                query = query.Where(t => t.Date >= startDate.Value);
            
            if (endDate.HasValue)
                query = query.Where(t => t.Date <= endDate.Value);
            
            var transactions = await query.OrderByDescending(t => t.Date).ToListAsync();
            
            // Получаем пользователей для транзакций
            var userIds = transactions.Select(t => t.UserId).Distinct();
            var users = await _db.Users
                .Where(u => userIds.Contains(u.Id))
                .ToDictionaryAsync(u => u.Id, u => u.Username);
            
            return transactions.Select(t => new TransactionResponseDto
            {
                Id = t.Id,
                Amount = t.Amount,
                Category = t.Category,
                Description = t.Description,
                Date = t.Date,
                IsIncome = t.IsIncome,
                CategoryColor = t.CategoryColor,
                CategoryIcon = t.CategoryIcon,
                UserId = t.UserId,
                Username = users.GetValueOrDefault(t.UserId, "")
            }).ToList();
        }
        
        public async Task<TransactionResponseDto?> GetByIdAsync(int id)
        {
            var transaction = await _db.Transactions.FindAsync(id);
            if (transaction == null) return null;
            
            var user = await _db.Users.FindAsync(transaction.UserId);
            
            return new TransactionResponseDto
            {
                Id = transaction.Id,
                Amount = transaction.Amount,
                Category = transaction.Category,
                Description = transaction.Description,
                Date = transaction.Date,
                IsIncome = transaction.IsIncome,
                CategoryColor = transaction.CategoryColor,
                CategoryIcon = transaction.CategoryIcon,
                UserId = transaction.UserId,
                Username = user?.Username ?? ""
            };
        }
        
        public async Task<TransactionResponseDto> CreateAsync(TransactionCreateDto dto, int userId)
        {
            // Get category info
            var category = await _categoryService.GetCategoryByNameAsync(dto.Category);
            
            var transaction = new Transaction
            {
                Amount = dto.Amount,
                Category = dto.Category,
                Description = dto.Description,
                IsIncome = dto.IsIncome,
                CategoryColor = category?.Color ?? dto.CategoryColor,
                CategoryIcon = category?.Icon ?? dto.CategoryIcon,
                UserId = userId,
                Date = DateTime.UtcNow
            };
            
            // Update category usage count
            if (category != null)
            {
                category.UsageCount++;
                await _categoryService.UpdateCategoryAsync(category);
            }
            
            _db.Transactions.Add(transaction);
            await _db.SaveChangesAsync();
            
            var user = await _db.Users.FindAsync(userId);
            
            return new TransactionResponseDto
            {
                Id = transaction.Id,
                Amount = transaction.Amount,
                Category = transaction.Category,
                Description = transaction.Description,
                Date = transaction.Date,
                IsIncome = transaction.IsIncome,
                CategoryColor = transaction.CategoryColor,
                CategoryIcon = transaction.CategoryIcon,
                UserId = transaction.UserId,
                Username = user?.Username ?? ""
            };
        }
        
        // ДОБАВЛЯЕМ ЭТОТ МЕТОД
        public async Task<bool> UpdateAsync(int id, TransactionUpdateDto dto, int userId)
        {
            var transaction = await _db.Transactions.FindAsync(id);
            if (transaction == null) return false;
            
            // Check ownership (unless admin)
            if (transaction.UserId != userId)
            {
                var user = await _db.Users.FindAsync(userId);
                if (user?.Role != "Admin") return false;
            }
            
            if (dto.Amount.HasValue) transaction.Amount = dto.Amount.Value;
            if (!string.IsNullOrEmpty(dto.Category))
            {
                var oldCategory = transaction.Category;
                transaction.Category = dto.Category;
                
                // Update category usage counts
                if (oldCategory != dto.Category)
                {
                    var oldCat = await _categoryService.GetCategoryByNameAsync(oldCategory);
                    if (oldCat != null && oldCat.UsageCount > 0)
                    {
                        oldCat.UsageCount--;
                        await _categoryService.UpdateCategoryAsync(oldCat);
                    }
                    
                    var newCat = await _categoryService.GetCategoryByNameAsync(dto.Category);
                    if (newCat != null)
                    {
                        newCat.UsageCount++;
                        await _categoryService.UpdateCategoryAsync(newCat);
                    }
                }
            }
            if (dto.Description != null) transaction.Description = dto.Description;
            if (dto.IsIncome.HasValue) transaction.IsIncome = dto.IsIncome.Value;
            
            _db.Transactions.Update(transaction);
            await _db.SaveChangesAsync();
            
            return true;
        }
        
        public async Task<bool> DeleteAsync(int id, int userId)
        {
            var transaction = await _db.Transactions.FindAsync(id);
            if (transaction == null) return false;
            
            // Check ownership (unless admin)
            if (transaction.UserId != userId)
            {
                var user = await _db.Users.FindAsync(userId);
                if (user?.Role != "Admin") return false;
            }
            
            // Update category usage count
            var category = await _categoryService.GetCategoryByNameAsync(transaction.Category);
            if (category != null && category.UsageCount > 0)
            {
                category.UsageCount--;
                await _categoryService.UpdateCategoryAsync(category);
            }
            
            _db.Transactions.Remove(transaction);
            await _db.SaveChangesAsync();
            
            return true;
        }
        
        public async Task<StatsResponseDto> GetStatsAsync(int userId, DateTime? startDate = null, DateTime? endDate = null)
        {
            var query = _db.Transactions.Where(t => t.UserId == userId);
            
            if (startDate.HasValue)
                query = query.Where(t => t.Date >= startDate.Value);
            
            if (endDate.HasValue)
                query = query.Where(t => t.Date <= endDate.Value);
            
            var transactions = await query.ToListAsync();
            
            var totalIncome = transactions
                .Where(t => t.IsIncome)
                .Sum(t => t.Amount);
            
            var totalExpense = transactions
                .Where(t => !t.IsIncome)
                .Sum(t => t.Amount);
            
            // Category stats for expenses
            var expenseByCategory = transactions
                .Where(t => !t.IsIncome)
                .GroupBy(t => t.Category)
                .Select(g => new CategoryStatsDto
                {
                    Category = g.Key,
                    Amount = g.Sum(t => t.Amount),
                    Color = g.First().CategoryColor,
                    Icon = g.First().CategoryIcon
                })
                .OrderByDescending(c => c.Amount)
                .ToList();
            
            var totalExpenseSum = expenseByCategory.Sum(c => c.Amount);
            
            if (totalExpenseSum > 0)
            {
                foreach (var category in expenseByCategory)
                {
                    category.Percentage = (category.Amount / totalExpenseSum) * 100;
                }
            }
            
            // Monthly stats
            var monthlyStats = transactions
                .GroupBy(t => new { t.Date.Year, t.Date.Month })
                .Select(g => new MonthlyStatsDto
                {
                    Month = $"{g.Key.Year}-{g.Key.Month:00}",
                    Income = g.Where(t => t.IsIncome).Sum(t => t.Amount),
                    Expense = g.Where(t => !t.IsIncome).Sum(t => t.Amount),
                    Balance = g.Where(t => t.IsIncome).Sum(t => t.Amount) - g.Where(t => !t.IsIncome).Sum(t => t.Amount)
                })
                .OrderByDescending(m => m.Month)
                .ToList();
            
            return new StatsResponseDto
            {
                TotalIncome = totalIncome,
                TotalExpense = totalExpense,
                Balance = totalIncome - totalExpense,
                CategoryStats = expenseByCategory,
                MonthlyStats = monthlyStats
            };
        }
    }
}
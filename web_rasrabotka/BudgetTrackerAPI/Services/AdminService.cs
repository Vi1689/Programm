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
        
        public async Task<List<User>> GetAllUsersAsync()
        {
            return await _db.Users
                .OrderBy(u => u.Id)
                .ToListAsync();
        }
        
        public async Task<User?> GetUserByIdAsync(int id)
        {
            return await _db.Users.FindAsync(id);
        }
        
        public async Task<bool> DeleteUserAsync(int id)
        {
            var user = await _db.Users.FindAsync(id);
            if (user == null) return false;
            
            // Can't delete admin accounts (or add logic to prevent deleting yourself)
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
            
            // Исправляем ошибку SQLite с суммированием decimal
            var allTransactions = await _db.Transactions.ToListAsync();
            
            var totalIncome = allTransactions
                .Where(t => t.IsIncome)
                .Sum(t => t.Amount);
            
            var totalExpense = allTransactions
                .Where(t => !t.IsIncome)
                .Sum(t => t.Amount);
            
            // Для последних транзакций используем DTO без циклических зависимостей
            var recentTransactions = await _db.Transactions
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
                    UserId = t.UserId
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
    }
}
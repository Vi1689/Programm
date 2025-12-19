using System.ComponentModel.DataAnnotations;

namespace BudgetAPI.Models.DTOs
{
    public class TransactionCreateDto
    {
        [Required(ErrorMessage = "Сумма обязательна")]
        [Range(0.01, double.MaxValue, ErrorMessage = "Сумма должна быть больше 0")]
        public decimal Amount { get; set; }
        
        [Required(ErrorMessage = "Категория обязательна")]
        [StringLength(50)]
        public string Category { get; set; } = string.Empty;
        
        [StringLength(200)]
        public string Description { get; set; } = string.Empty;
        
        public bool IsIncome { get; set; }
        
        public string CategoryColor { get; set; } = "#808080";
        
        public string CategoryIcon { get; set; } = "💰";
    }
    
    public class TransactionResponseDto
    {
        public int Id { get; set; }
        public decimal Amount { get; set; }
        public string Category { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public DateTime Date { get; set; }
        public bool IsIncome { get; set; }
        public string CategoryColor { get; set; } = "#808080";
        public string CategoryIcon { get; set; } = "💰";
        public int UserId { get; set; }
        public string Username { get; set; } = string.Empty;
    }
    
    public class TransactionUpdateDto
    {
        public decimal? Amount { get; set; }
        public string? Category { get; set; }
        public string? Description { get; set; }
        public bool? IsIncome { get; set; }
    }
    
    public class StatsResponseDto
    {
        public decimal TotalIncome { get; set; }
        public decimal TotalExpense { get; set; }
        public decimal Balance { get; set; }
        public List<CategoryStatsDto> CategoryStats { get; set; } = new();
        public List<MonthlyStatsDto> MonthlyStats { get; set; } = new();
    }
    
    public class CategoryStatsDto
    {
        public string Category { get; set; } = string.Empty;
        public string Icon { get; set; } = "💰";
        public decimal Amount { get; set; }
        public string Color { get; set; } = "#808080";
        public decimal Percentage { get; set; }
    }
    
    public class MonthlyStatsDto
    {
        public string Month { get; set; } = string.Empty;
        public decimal Income { get; set; }
        public decimal Expense { get; set; }
        public decimal Balance { get; set; }
    }
}
using System.ComponentModel.DataAnnotations;

namespace BudgetAPI.Models
{
    public class Transaction
    {
        public int Id { get; set; }
        
        [Required]
        [Range(0.01, double.MaxValue, ErrorMessage = "Сумма должна быть больше 0")]
        public decimal Amount { get; set; }
        
        [Required]
        [StringLength(50)]
        public string Category { get; set; } = "Other";
        
        [StringLength(200)]
        public string Description { get; set; } = string.Empty;
        
        public DateTime Date { get; set; } = DateTime.UtcNow;
        
        public bool IsIncome { get; set; } // true - доход, false - расход
        
        public string CategoryColor { get; set; } = "#808080";
        
        public string CategoryIcon { get; set; } = "💰";
        
        // Foreign key
        public int UserId { get; set; }
        
        // Navigation property
        public User? User { get; set; }
    }
}
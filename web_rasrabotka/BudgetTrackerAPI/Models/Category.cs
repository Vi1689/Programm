using System.ComponentModel.DataAnnotations;

namespace BudgetAPI.Models
{
    public class Category
    {
        public int Id { get; set; }
        
        [Required]
        [StringLength(50)]
        public string Name { get; set; } = string.Empty;
        
        public string Icon { get; set; } = "💰";
        
        public string Color { get; set; } = "#808080";
        
        public bool IsSystem { get; set; } = true; // Системная категория (нельзя удалить)
        
        public string Type { get; set; } = "Expense"; // "Expense" или "Income"
        
        public int UsageCount { get; set; } = 0;
        
        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
    }
}
using System.ComponentModel.DataAnnotations;

namespace BudgetAPI.Models.DTOs
{
    public class CategoryCreateDto
    {
        [Required(ErrorMessage = "Название категории обязательно")]
        [StringLength(50, ErrorMessage = "Название не должно превышать 50 символов")]
        public string Name { get; set; } = string.Empty;
        
        public string Icon { get; set; } = "💰";
        
        [RegularExpression("^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$", ErrorMessage = "Некорректный цвет")]
        public string Color { get; set; } = "#808080";
        
        [Required(ErrorMessage = "Тип категории обязателен")]
        public string Type { get; set; } = "Expense"; // "Expense" или "Income"
    }
    
    public class CategoryResponseDto
    {
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public string Icon { get; set; } = "💰";
        public string Color { get; set; } = "#808080";
        public string Type { get; set; } = "Expense";
        public bool IsSystem { get; set; }
        public int UsageCount { get; set; }
        public DateTime CreatedAt { get; set; }
    }
    
    public class PopularCategoryDto
    {
        public string Name { get; set; } = string.Empty;
        public string Icon { get; set; } = "💰";
        public string Color { get; set; } = "#808080";
        public string Type { get; set; } = "Expense";
        public int UsageCount { get; set; }
    }
}
using System.ComponentModel.DataAnnotations;

namespace ValeraAPI.Models
{
    public class User
    {
        public int Id { get; set; }
        
        [Required]
        [EmailAddress]
        public string Email { get; set; } = string.Empty;
        
        [Required]
        public string Username { get; set; } = string.Empty;
        
        [Required]
        public string PasswordHash { get; set; } = string.Empty;
        
        public string Role { get; set; } = "User"; // "User" или "Admin"
        
        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
        
        // Связь с Валерами
        public List<Valera> Valeras { get; set; } = new();
    }
}
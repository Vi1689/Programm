using Microsoft.EntityFrameworkCore;
using ValeraAPI.Models;

namespace ValeraAPI.Data;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options)
    {
    }

    public DbSet<Valera> Valeras { get; set; }
    public DbSet<User> Users { get; set; }
    
    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);
        
        // Настройка связи один-ко-многим
        modelBuilder.Entity<Valera>()
            .HasOne(v => v.User)
            .WithMany(u => u.Valeras)
            .HasForeignKey(v => v.UserId)
            .OnDelete(DeleteBehavior.Cascade);
        
        // Уникальный индекс для email
        modelBuilder.Entity<User>()
            .HasIndex(u => u.Email)
            .IsUnique();
    }
}
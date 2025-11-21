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
}

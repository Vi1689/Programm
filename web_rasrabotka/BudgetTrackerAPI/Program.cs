using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using System.Text;
using BudgetAPI.Data;
using BudgetAPI.Services;
using BudgetAPI.Models;

var builder = WebApplication.CreateBuilder(args);

// CORS
builder.Services.AddCors(options =>
{
    options.AddDefaultPolicy(policy =>
    {
        policy.WithOrigins("http://localhost:3000", "http://localhost:3001")
              .AllowAnyHeader()
              .AllowAnyMethod()
              .AllowCredentials();
    });
});

// Controllers
builder.Services.AddControllers()
    .AddJsonOptions(options =>
    {
        options.JsonSerializerOptions.PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase;
        options.JsonSerializerOptions.ReferenceHandler = System.Text.Json.Serialization.ReferenceHandler.IgnoreCycles; 
    });

// Swagger
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// Database
builder.Services.AddDbContext<AppDbContext>(options =>
    options.UseSqlite("Data Source=budget.db"));

// Services
builder.Services.AddScoped<AuthService>();
builder.Services.AddScoped<TransactionService>();
builder.Services.AddScoped<CategoryService>();
builder.Services.AddScoped<AdminService>();

// JWT Authentication
var jwtKey = builder.Configuration["Jwt:Key"] ?? "SuperSecretKeyForBudgetApp2024";
var jwtIssuer = builder.Configuration["Jwt:Issuer"] ?? "BudgetAPI";
var jwtAudience = builder.Configuration["Jwt:Audience"] ?? "BudgetClient";

builder.Services.AddAuthentication(options =>
{
    options.DefaultAuthenticateScheme = JwtBearerDefaults.AuthenticationScheme;
    options.DefaultChallengeScheme = JwtBearerDefaults.AuthenticationScheme;
})
.AddJwtBearer(options =>
{
    options.TokenValidationParameters = new TokenValidationParameters
    {
        ValidateIssuer = true,
        ValidateAudience = true,
        ValidateLifetime = true,
        ValidateIssuerSigningKey = true,
        ValidIssuer = jwtIssuer,
        ValidAudience = jwtAudience,
        IssuerSigningKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(jwtKey))
    };
});

builder.Services.AddAuthorization();

var app = builder.Build();

// Initialize database
using (var scope = app.Services.CreateScope())
{
    var db = scope.ServiceProvider.GetRequiredService<AppDbContext>();
    db.Database.Migrate();
    
    // Create default admin if not exists
    if (!db.Users.Any(u => u.Role == "Admin"))
    {
        var admin = new User
        {
            Email = "admin@admin.com",
            Username = "admin",
            Role = "Admin",
            CreatedAt = DateTime.UtcNow
        };
        
        // Используйте стандартный PasswordHasher из Microsoft.AspNetCore.Identity
        var passwordHasher = new PasswordHasher<User>();
        admin.PasswordHash = passwordHasher.HashPassword(admin, "admin123");
        
        db.Users.Add(admin);
        db.SaveChanges();
    }
    
    // Create default categories if not exists
    if (!db.Categories.Any())
    {
        var defaultCategories = new List<Category>
        {
            // Expenses
            new Category { Name = "Еда", Icon = "🍔", Color = "#FF6B6B", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Транспорт", Icon = "🚗", Color = "#4ECDC4", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Развлечения", Icon = "🎬", Color = "#45B7D1", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Одежда", Icon = "👕", Color = "#96CEB4", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Спорт", Icon = "🏋️", Color = "#FECA57", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Здоровье", Icon = "🏥", Color = "#FF9FF3", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Образование", Icon = "📚", Color = "#54A0FF", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Другое", Icon = "💰", Color = "#808080", Type = "Expense", IsSystem = true, CreatedAt = DateTime.UtcNow },
            
            // Income
            new Category { Name = "Зарплата", Icon = "💼", Color = "#2ECC71", Type = "Income", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Инвестиции", Icon = "📈", Color = "#9B59B6", Type = "Income", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Подарки", Icon = "🎁", Color = "#F1C40F", Type = "Income", IsSystem = true, CreatedAt = DateTime.UtcNow },
            new Category { Name = "Другое", Icon = "💵", Color = "#95A5A6", Type = "Income", IsSystem = true, CreatedAt = DateTime.UtcNow }
        };
        
        db.Categories.AddRange(defaultCategories);
        db.SaveChanges();
    }
}

// Middleware
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();
app.UseCors();
app.UseAuthentication();
app.UseAuthorization();
app.MapControllers();
app.Run();
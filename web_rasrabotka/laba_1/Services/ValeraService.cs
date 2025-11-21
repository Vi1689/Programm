using Microsoft.EntityFrameworkCore;
using ValeraAPI.Data;
using ValeraAPI.Models;

namespace ValeraAPI.Services
{
    public class ValeraService
    {
        private readonly AppDbContext _context;

        public ValeraService(AppDbContext context)
        {
            _context = context;
        }

        public async Task<List<Valera>> GetAllAsync()
        {
            return await _context.Valeras.ToListAsync();
        }

        public async Task<Valera?> GetByIdAsync(int id)
        {
            return await _context.Valeras.FindAsync(id);
        }

        public async Task<Valera> CreateAsync(Valera valera)
        {
            _context.Valeras.Add(valera);
            await _context.SaveChangesAsync();
            return valera;
        }

        public async Task<bool> UpdateAsync(Valera valera)
        {
            _context.Valeras.Update(valera);
            await _context.SaveChangesAsync();
            return true;
        }

        public async Task<bool> DeleteAsync(int id)
        {
            var valera = await _context.Valeras.FindAsync(id);
            if (valera == null) return false;

            _context.Valeras.Remove(valera);
            await _context.SaveChangesAsync();
            return true;
        }
    }
}

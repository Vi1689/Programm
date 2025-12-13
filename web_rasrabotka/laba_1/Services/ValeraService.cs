using Microsoft.EntityFrameworkCore;
using ValeraAPI.Data;
using ValeraAPI.Models;

namespace ValeraAPI.Services
{
    public class ValeraService
    {
        private readonly AppDbContext _db;
        public ValeraService(AppDbContext db) => _db = db;

        // НОВОЕ: Админ видит всех
        public async Task<List<Valera>> GetAllAsync() => await _db.Valeras.ToListAsync();

        // НОВОЕ: Пользователь видит только своих
        public async Task<List<Valera>> GetMyAsync(int userId) => 
            await _db.Valeras.Where(v => v.UserId == userId).ToListAsync();

        public async Task<Valera?> GetByIdAsync(int id) => await _db.Valeras.FindAsync(id);

        // ИЗМЕНЕНО: Добавлен userId
        public async Task<Valera> CreateAsync(Valera v, int userId)
        {
            v.UserId = userId;
            _db.Valeras.Add(v);
            await _db.SaveChangesAsync();
            return v;
        }

        public async Task<bool> UpdateAsync(Valera v)
        {
            var exist = await _db.Valeras.FindAsync(v.Id);
            if (exist is null) return false;

            exist = MapToExisting(exist, v);
            _db.Valeras.Update(exist);
            await _db.SaveChangesAsync();
            return true;
        }

        private Valera MapToExisting(Valera to, Valera from)
        {
            try
            {
                var nameProp = typeof(Valera).GetProperty("Name");
                if (nameProp != null && nameProp.CanWrite) nameProp.SetValue(to, from.Name);

                var moneyProp = typeof(Valera).GetProperty("Money");
                if (moneyProp != null && moneyProp.CanWrite) moneyProp.SetValue(to, from.Money);
            }
            catch {  }

            return to;
        }

        public async Task<bool> DeleteAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return false;
            _db.Valeras.Remove(v);
            await _db.SaveChangesAsync();
            return true;
        }

        // НОВОЕ: Проверка владения
        public async Task<bool> IsOwnerAsync(int valeraId, int userId)
        {
            var valera = await _db.Valeras.FindAsync(valeraId);
            return valera != null && valera.UserId == userId;
        }

        public async Task<(bool Success, string? Error, Valera? Valera)> WorkAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return (false, "NotFound", null);

            var ok = v.GoWork();
            if (!ok) return (false, "CannotWorkNow", v);

            await _db.SaveChangesAsync();
            return (true, null, v);
        }

        public async Task<(bool Success, Valera? Valera)> NatureAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return (false, null);
            v.ContemplateNature();
            await _db.SaveChangesAsync();
            return (true, v);
        }

        public async Task<(bool Success, Valera? Valera)> WineAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return (false, null);
            v.DrinkWineAndWatchSeries();
            await _db.SaveChangesAsync();
            return (true, v);
        }

        public async Task<(bool Success, Valera? Valera)> BarAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return (false, null);
            v.GoBar();
            await _db.SaveChangesAsync();
            return (true, v);
        }

        public async Task<(bool Success, Valera? Valera)> MarginalsAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return (false, null);
            v.DrinkWithMarginals();
            await _db.SaveChangesAsync();
            return (true, v);
        }

        public async Task<(bool Success, Valera? Valera)> MetroAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return (false, null);
            v.SingInMetro();
            await _db.SaveChangesAsync();
            return (true, v);
        }

        public async Task<(bool Success, Valera? Valera)> SleepAsync(int id)
        {
            var v = await _db.Valeras.FindAsync(id);
            if (v == null) return (false, null);
            v.Sleep();
            await _db.SaveChangesAsync();
            return (true, v);
        }
    }
}
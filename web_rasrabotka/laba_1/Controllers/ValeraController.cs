using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using ValeraAPI.Models;
using ValeraAPI.Services;

namespace ValeraAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    [Authorize] // НОВОЕ: Все методы требуют авторизации
    public class ValeraController : ControllerBase
    {
        private readonly ValeraService _service;
        public ValeraController(ValeraService service) => _service = service;

        // НОВОЕ: Вспомогательные методы
        private int GetUserId() => int.Parse(User.FindFirst(ClaimTypes.NameIdentifier)?.Value ?? "0");
        private bool IsAdmin() => User.IsInRole("Admin");

        // ИЗМЕНЕНО: Только для админов - все Валеры
        [HttpGet]
        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> GetAll() => Ok(await _service.GetAllAsync());

        // НОВОЕ: Для обычных пользователей - только свои Валеры
        [HttpGet("my")]
        public async Task<IActionResult> GetMy() => Ok(await _service.GetMyAsync(GetUserId()));

        // ИЗМЕНЕНО: Проверка прав доступа
        [HttpGet("{id}")]
        public async Task<IActionResult> Get(int id)
        {
            var v = await _service.GetByIdAsync(id);
            if (v is null) return NotFound();

            // НОВОЕ: Проверка прав доступа
            if (!IsAdmin() && v.UserId != GetUserId())
                return Forbid();

            return Ok(v);
        }

        // ИЗМЕНЕНО: Передается userId
        [HttpPost]
        public async Task<IActionResult> Create([FromBody] Valera v)
        {
            var created = await _service.CreateAsync(v, GetUserId());
            return CreatedAtAction(nameof(Get), new { id = created.Id }, created);
        }

        // ИЗМЕНЕНО: Проверка прав
        [HttpPut("{id}")]
        public async Task<IActionResult> Update(int id, [FromBody] Valera input)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();

            // НОВОЕ: Проверка прав доступа
            if (!IsAdmin() && existing.UserId != GetUserId())
                return Forbid();

            if (id != input.Id) input.Id = id;
            var ok = await _service.UpdateAsync(input);
            return ok ? Ok(input) : NotFound();
        }

        // ИЗМЕНЕНО: Проверка прав
        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();

            // НОВОЕ: Проверка прав доступа
            if (!IsAdmin() && existing.UserId != GetUserId())
                return Forbid();

            var ok = await _service.DeleteAsync(id);
            return ok ? Ok() : NotFound();
        }

        // ИЗМЕНЕНО: Все действия с проверкой прав
        [HttpPost("{id}/work")]
        public async Task<IActionResult> Work(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();

            if (!IsAdmin() && existing.UserId != GetUserId())
                return Forbid();

            var (success, error, valera) = await _service.WorkAsync(id);
            if (!success)
            {
                if (error == "NotFound") return NotFound();
                if (error == "CannotWorkNow") return BadRequest("Cannot work now: alcohol >=50 or fatigue >=10");
                return BadRequest();
            }
            return Ok(valera);
        }

        [HttpPost("{id}/nature")]
        public async Task<IActionResult> Nature(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();
            if (!IsAdmin() && existing.UserId != GetUserId()) return Forbid();

            var (success, valera) = await _service.NatureAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/wine")]
        public async Task<IActionResult> Wine(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();
            if (!IsAdmin() && existing.UserId != GetUserId()) return Forbid();

            var (success, valera) = await _service.WineAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/bar")]
        public async Task<IActionResult> Bar(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();
            if (!IsAdmin() && existing.UserId != GetUserId()) return Forbid();

            var (success, valera) = await _service.BarAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/marginals")]
        public async Task<IActionResult> Marginals(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();
            if (!IsAdmin() && existing.UserId != GetUserId()) return Forbid();

            var (success, valera) = await _service.MarginalsAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/metro")]
        public async Task<IActionResult> Metro(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();
            if (!IsAdmin() && existing.UserId != GetUserId()) return Forbid();

            var (success, valera) = await _service.MetroAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/sleep")]
        public async Task<IActionResult> Sleep(int id)
        {
            var existing = await _service.GetByIdAsync(id);
            if (existing is null) return NotFound();
            if (!IsAdmin() && existing.UserId != GetUserId()) return Forbid();

            var (success, valera) = await _service.SleepAsync(id);
            return success ? Ok(valera) : NotFound();
        }
    }
}
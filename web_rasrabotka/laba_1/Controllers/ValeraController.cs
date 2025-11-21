using Microsoft.AspNetCore.Mvc;
using ValeraAPI.Models;
using ValeraAPI.Services;

namespace ValeraAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class ValeraController : ControllerBase
    {
        private readonly ValeraService _service;
        public ValeraController(ValeraService service) => _service = service;

        [HttpGet]
        public async Task<IActionResult> GetAll() => Ok(await _service.GetAllAsync());

        [HttpGet("{id}")]
        public async Task<IActionResult> Get(int id)
        {
            var v = await _service.GetByIdAsync(id);
            return v is null ? NotFound() : Ok(v);
        }

        [HttpPost]
        public async Task<IActionResult> Create([FromBody] Valera v)
        {
            var created = await _service.CreateAsync(v);
            return CreatedAtAction(nameof(Get), new { id = created.Id }, created);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Update(int id, [FromBody] Valera input)
        {
            if (id != input.Id) input.Id = id;
            var ok = await _service.UpdateAsync(input);
            return ok ? Ok(input) : NotFound();
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            var ok = await _service.DeleteAsync(id);
            return ok ? Ok() : NotFound();
        }

        [HttpPost("{id}/work")]
        public async Task<IActionResult> Work(int id)
        {
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
            var (success, valera) = await _service.NatureAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/wine")]
        public async Task<IActionResult> Wine(int id)
        {
            var (success, valera) = await _service.WineAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/bar")]
        public async Task<IActionResult> Bar(int id)
        {
            var (success, valera) = await _service.BarAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/marginals")]
        public async Task<IActionResult> Marginals(int id)
        {
            var (success, valera) = await _service.MarginalsAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/metro")]
        public async Task<IActionResult> Metro(int id)
        {
            var (success, valera) = await _service.MetroAsync(id);
            return success ? Ok(valera) : NotFound();
        }

        [HttpPost("{id}/sleep")]
        public async Task<IActionResult> Sleep(int id)
        {
            var (success, valera) = await _service.SleepAsync(id);
            return success ? Ok(valera) : NotFound();
        }
    }
}

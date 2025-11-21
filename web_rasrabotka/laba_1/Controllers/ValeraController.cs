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

        public ValeraController(ValeraService service)
        {
            _service = service;
        }

        [HttpGet]
        public async Task<IActionResult> GetAll()
        {
            return Ok(await _service.GetAllAsync());
        }

        [HttpGet("{id}")]
        public async Task<IActionResult> GetById(int id)
        {
            var valera = await _service.GetByIdAsync(id);
            return valera == null ? NotFound() : Ok(valera);
        }

        [HttpPost]
        public async Task<IActionResult> Create(Valera valera)
        {
            var created = await _service.CreateAsync(valera);
            return CreatedAtAction(nameof(GetById), new { id = created.Id }, created);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Update(int id, Valera valera)
        {
            if (id != valera.Id)
                return BadRequest();

            await _service.UpdateAsync(valera);
            return Ok(valera);
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            var result = await _service.DeleteAsync(id);
            return result ? Ok() : NotFound();
        }
    }
}

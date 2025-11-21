const API_ROOT = "http://localhost:5097/api/valera";

export async function getAllValeras() { return fetch(API_ROOT).then(r=>r.json()); }
export async function getValera(id) { return fetch(`${API_ROOT}/${id}`).then(r=>r.json()); }
export async function createValera(data) { return fetch(API_ROOT, { method:'POST', headers:{'Content-Type':'application/json'}, body:JSON.stringify(data)}).then(r=>r.json()); }
export async function action(id, act) { return fetch(`${API_ROOT}/${id}/${act}`, { method: 'POST' }).then(async r => r.json()); }

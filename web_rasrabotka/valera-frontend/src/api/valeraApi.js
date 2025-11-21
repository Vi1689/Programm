const API_URL = "http://localhost:5097/api/valera";

export async function getAllValeras() {
    return fetch(API_URL).then(r => r.json());
}

export async function getValera(id) {
    return fetch(`${API_URL}/${id}`).then(r => r.json());
}

export async function createValera(data) {
    return fetch(API_URL, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(data)
    });
}

export async function action(id, act) {
    return fetch(`${API_URL}/${id}/${act}`, { method: "POST" });
}

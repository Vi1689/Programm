const API_ROOT = "http://localhost:5097/api";

// Получение заголовков с токеном
const getHeaders = () => {
  const token = localStorage.getItem('token');
  return {
    'Content-Type': 'application/json',
    ...(token && { 'Authorization': `Bearer ${token}` })
  };
};

// ============= Auth endpoints =============
export async function register(data) {
  return fetch(`${API_ROOT}/auth/register`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(data)
  }).then(r => r.json());
}

export async function login(data) {
  return fetch(`${API_ROOT}/auth/login`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(data)
  }).then(r => r.json());
}

// ============= Valera endpoints =============

// Получить всех Валер (только для админа)
export async function getAllValeras() {
  return fetch(`${API_ROOT}/valera`, {
    headers: getHeaders()
  }).then(r => r.json());
}

// Получить своих Валер (для обычных пользователей)
export async function getMyValeras() {
  return fetch(`${API_ROOT}/valera/my`, {
    headers: getHeaders()
  }).then(r => r.json());
}

// Получить конкретную Валеру
export async function getValera(id) {
  return fetch(`${API_ROOT}/valera/${id}`, {
    headers: getHeaders()
  }).then(r => r.json());
}

// Создать Валеру
export async function createValera(data) {
  return fetch(`${API_ROOT}/valera`, {
    method: 'POST',
    headers: getHeaders(),
    body: JSON.stringify(data)
  }).then(r => r.json());
}

// Удалить Валеру
export async function deleteValera(id) {
  return fetch(`${API_ROOT}/valera/${id}`, {
    method: 'DELETE',
    headers: getHeaders()
  });
}

// Выполнить действие
export async function action(id, act) {
  return fetch(`${API_ROOT}/valera/${id}/${act}`, {
    method: 'POST',
    headers: getHeaders()
  }).then(async r => {
    if (!r.ok) throw new Error(await r.text());
    return r.json();
  });
}
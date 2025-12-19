const API_ROOT = "http://localhost:5256/api";

const getHeaders = () => {
  const token = localStorage.getItem('budget_token');
  return {
    'Content-Type': 'application/json',
    ...(token && { 'Authorization': `Bearer ${token}` })
  };
};

// Проверка ответа сервера
const handleResponse = async (response) => {
  const contentType = response.headers.get('content-type');
  
  if (!response.ok) {
    let errorMessage = `Ошибка ${response.status}: ${response.statusText}`;
    
    try {
      if (contentType && contentType.includes('application/json')) {
        const errorData = await response.json();
        
        // Проверяем разные форматы ошибок
        if (errorData.message) {
          errorMessage = errorData.message;
        } else if (errorData.title) {
          errorMessage = errorData.title;
        } else if (typeof errorData === 'string') {
          errorMessage = errorData;
        } else if (errorData.errors) {
          // Для ошибок валидации ModelState
          const errors = Object.values(errorData.errors).flat();
          errorMessage = errors.join(', ');
        }
      } else {
        const errorText = await response.text();
        if (errorText) errorMessage = errorText;
      }
    } catch (parseError) {
      console.error('Ошибка парсинга ответа:', parseError);
    }
    
    throw new Error(errorMessage);
  }
  
  // Для пустых ответов
  if (response.status === 204) {
    return null;
  }
  
  if (contentType && contentType.includes('application/json')) {
    return response.json();
  }
  
  return response.text();
};


// Аутентификация
export async function register(data) {
  const response = await fetch(`${API_ROOT}/auth/register`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(data)
  });
  return handleResponse(response);
}

export async function login(data) {
  const response = await fetch(`${API_ROOT}/auth/login`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(data)
  });
  return handleResponse(response);
}

// Транзакции
export async function getAllTransactions(startDate, endDate) {
  let url = `${API_ROOT}/transaction`;
  const params = new URLSearchParams();
  if (startDate) params.append('startDate', startDate.toISOString());
  if (endDate) params.append('endDate', endDate.toISOString());
  
  const queryString = params.toString();
  if (queryString) url += `?${queryString}`;
  
  const response = await fetch(url, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function getMyTransactions(startDate, endDate) {
  let url = `${API_ROOT}/transaction/my`;
  const params = new URLSearchParams();
  if (startDate) params.append('startDate', startDate.toISOString());
  if (endDate) params.append('endDate', endDate.toISOString());
  
  const queryString = params.toString();
  if (queryString) url += `?${queryString}`;
  
  const response = await fetch(url, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function getTransaction(id) {
  const response = await fetch(`${API_ROOT}/transaction/${id}`, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function createTransaction(data) {
  const response = await fetch(`${API_ROOT}/transaction`, {
    method: 'POST',
    headers: getHeaders(),
    body: JSON.stringify(data)
  });
  return handleResponse(response);
}

export async function updateTransaction(id, data) {
  const response = await fetch(`${API_ROOT}/transaction/${id}`, {
    method: 'PUT',
    headers: getHeaders(),
    body: JSON.stringify(data)
  });
  return handleResponse(response);
}

export async function deleteTransaction(id) {
  const response = await fetch(`${API_ROOT}/transaction/${id}`, {
    method: 'DELETE',
    headers: getHeaders()
  });
  
  if (!response.ok) {
    const errorText = await response.text();
    throw new Error(errorText || 'Ошибка удаления');
  }
  
  return true;
}

export async function getStats(startDate, endDate) {
  let url = `${API_ROOT}/transaction/stats`;
  const params = new URLSearchParams();
  if (startDate) params.append('startDate', startDate.toISOString());
  if (endDate) params.append('endDate', endDate.toISOString());
  
  const queryString = params.toString();
  if (queryString) url += `?${queryString}`;
  
  const response = await fetch(url, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

// Категории
export async function getCategories() {
  const response = await fetch(`${API_ROOT}/category`, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function getCategoriesByType(type) {
  const response = await fetch(`${API_ROOT}/category/type/${type}`, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function getPopularCategories(limit = 8) {
  const response = await fetch(`${API_ROOT}/category/popular?limit=${limit}`, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function createCategory(data) {
  const response = await fetch(`${API_ROOT}/category`, {
    method: 'POST',
    headers: getHeaders(),
    body: JSON.stringify(data)
  });
  return handleResponse(response);
}

export async function deleteCategory(id) {
  const response = await fetch(`${API_ROOT}/category/${id}`, {
    method: 'DELETE',
    headers: getHeaders()
  });
  
  if (!response.ok) {
    const errorText = await response.text();
    throw new Error(errorText || 'Ошибка удаления');
  }
  
  return true;
}

// Админ
export async function getAllUsers() {
  const response = await fetch(`${API_ROOT}/admin/users`, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function getAdminStats() {
  const response = await fetch(`${API_ROOT}/admin/stats`, {
    headers: getHeaders()
  });
  return handleResponse(response);
}

export async function updateUserRole(id, role) {
  const response = await fetch(`${API_ROOT}/admin/users/${id}/role`, {
    method: 'PUT',
    headers: getHeaders(),
    body: JSON.stringify({ role })
  });
  return handleResponse(response);
}

export async function deleteUser(id) {
  const response = await fetch(`${API_ROOT}/admin/users/${id}`, {
    method: 'DELETE',
    headers: getHeaders()
  });
  
  if (!response.ok) {
    const errorText = await response.text();
    throw new Error(errorText || 'Ошибка удаления');
  }
  
  return true;
}
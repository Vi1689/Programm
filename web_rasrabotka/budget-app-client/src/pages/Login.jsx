import React, { useState } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import { Form, Button, Card, Alert } from 'react-bootstrap';
import { login } from '../api/budgetApi';
import { useAuth } from '../context/AuthContext';

export default function Login() {
  const [formData, setFormData] = useState({ email: '', password: '' });
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(false);
  const navigate = useNavigate();
  const { login: authLogin } = useAuth();

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError('');
    setLoading(true);

    // Базовая валидация
    if (!formData.email || !formData.password) {
      setError('Заполните все поля');
      setLoading(false);
      return;
    }

    if (!formData.email.includes('@')) {
      setError('Введите корректный email');
      setLoading(false);
      return;
    }

    try {
      const response = await login(formData);
      
      // Проверяем, есть ли токен в ответе
      if (response && response.token) {
        authLogin(response.token, {
          userId: response.userId,
          email: response.email,
          username: response.username,
          role: response.role
        });
        navigate('/dashboard');
      } else {
        setError('Неверный ответ от сервера');
      }
    } catch (err) {
      console.error('Ошибка входа:', err);
      // Более информативное сообщение об ошибке
      if (err.message.includes('401') || err.message.includes('Неверный')) {
        setError('Неверный email или пароль');
      } else if (err.message.includes('NetworkError') || err.message.includes('Failed to fetch')) {
        setError('Ошибка соединения с сервером. Проверьте, запущен ли API на localhost:5256');
      } else {
        setError(err.message || 'Ошибка входа. Попробуйте снова.');
      }
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="container mt-5">
      <div className="row justify-content-center">
        <div className="col-md-6">
          <Card>
            <Card.Body>
              <h2 className="text-center mb-4">Войдите в систему для отслеживания бюджета</h2>
              
              {error && (
                <Alert 
                  variant="danger" 
                  onClose={() => setError('')} 
                  dismissible
                  className="mb-3"
                >
                  {error}
                </Alert>
              )}
              
              <Form onSubmit={handleSubmit}>
                <Form.Group className="mb-3">
                  <Form.Label>Email</Form.Label>
                  <Form.Control
                    type="email"
                    required
                    placeholder="your@email.com"
                    value={formData.email}
                    onChange={e => setFormData({...formData, email: e.target.value.trim()})}
                    disabled={loading}
                  />
                </Form.Group>

                <Form.Group className="mb-3">
                  <Form.Label>Пароль</Form.Label>
                  <Form.Control
                    type="password"
                    required
                    placeholder="Введите пароль"
                    value={formData.password}
                    onChange={e => setFormData({...formData, password: e.target.value})}
                    disabled={loading}
                  />
                </Form.Group>

                <Button 
                  variant="primary" 
                  type="submit" 
                  className="w-100"
                  disabled={loading}
                >
                  {loading ? 'Вход...' : 'Войти'}
                </Button>
              </Form>

              <div className="text-center mt-3">
                Нет аккаунта? <Link to="/register">Зарегистрироваться</Link>
              </div>
            </Card.Body>
          </Card>
        </div>
      </div>
    </div>
  );
}
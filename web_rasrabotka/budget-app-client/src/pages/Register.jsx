import React, { useState } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import { Form, Button, Card, Alert } from 'react-bootstrap';
import { register } from '../api/budgetApi';
import { useAuth } from '../context/AuthContext';

export default function Register() {
  const [formData, setFormData] = useState({ 
    email: '', 
    username: '', 
    password: '',
    confirmPassword: ''
  });
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(false);
  const navigate = useNavigate();
  const { login } = useAuth();

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError('');

    // Валидация на клиенте
    if (formData.password !== formData.confirmPassword) {
      setError('Пароли не совпадают');
      return;
    }

    if (formData.password.length < 6) {
      setError('Пароль должен быть не менее 6 символов');
      return;
    }

    if (formData.username.length < 3) {
      setError('Имя пользователя должно быть не менее 3 символов');
      return;
    }

    if (!formData.email.includes('@')) {
      setError('Введите корректный email');
      return;
    }

    setLoading(true);

    try {
      const { confirmPassword, ...dataToSend } = formData;
      const response = await register(dataToSend);
      
      if (response && response.token) {
        login(response.token, {
          userId: response.userId,
          email: response.email,
          username: response.username,
          role: response.role
        });
        navigate('/dashboard');
      } else {
        setError(response?.message || 'Ошибка регистрации');
      }
    } catch (err) {
      console.error('Ошибка регистрации:', err);
      // Более информативные сообщения об ошибках
      if (err.message.includes('Email уже используется')) {
        setError('Этот email уже зарегистрирован');
      } else if (err.message.includes('Имя пользователя уже используется')) {
        setError('Это имя пользователя уже занято');
      } else if (err.message.includes('NetworkError') || err.message.includes('Failed to fetch')) {
        setError('Ошибка соединения с сервером. Проверьте, запущен ли API на localhost:5256');
      } else {
        setError(err.message || 'Ошибка регистрации. Попробуйте снова.');
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
              <h2 className="text-center mb-4">Регистрация</h2>
              
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
                  <Form.Label>Имя пользователя</Form.Label>
                  <Form.Control
                    type="text"
                    required
                    minLength={3}
                    placeholder="Минимум 3 символа"
                    value={formData.username}
                    onChange={e => setFormData({...formData, username: e.target.value.trim()})}
                    disabled={loading}
                  />
                </Form.Group>

                <Form.Group className="mb-3">
                  <Form.Label>Пароль</Form.Label>
                  <Form.Control
                    type="password"
                    required
                    minLength={6}
                    placeholder="Минимум 6 символов"
                    value={formData.password}
                    onChange={e => setFormData({...formData, password: e.target.value})}
                    disabled={loading}
                  />
                </Form.Group>

                <Form.Group className="mb-3">
                  <Form.Label>Подтвердите пароль</Form.Label>
                  <Form.Control
                    type="password"
                    required
                    placeholder="Повторите пароль"
                    value={formData.confirmPassword}
                    onChange={e => setFormData({...formData, confirmPassword: e.target.value})}
                    disabled={loading}
                  />
                </Form.Group>

                <Button 
                  variant="primary" 
                  type="submit" 
                  className="w-100"
                  disabled={loading}
                >
                  {loading ? 'Регистрация...' : 'Зарегистрироваться'}
                </Button>
              </Form>

              <div className="text-center mt-3">
                Уже есть аккаунт? <Link to="/login">Войти</Link>
              </div>
            </Card.Body>
          </Card>
        </div>
      </div>
    </div>
  );
}
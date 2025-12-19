import React, { useState, useEffect, useCallback } from 'react';
import { 
  Button, Modal, Form, Alert, 
  Badge, Card, Row, Col 
} from 'react-bootstrap';
import { useAuth } from '../context/AuthContext';
import { 
  getCategories, getCategoriesByType, 
  createCategory, deleteCategory 
} from '../api/budgetApi';

export default function Categories() {
  const [categories, setCategories] = useState([]);
  const [filter, setFilter] = useState('all'); // all, expense, income
  const [showModal, setShowModal] = useState(false);
  const [formData, setFormData] = useState({
    name: '',
    icon: '💰',
    color: '#808080',
    type: 'Expense'
  });
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(true);
  const { isAdmin } = useAuth();

  // Используем useCallback для мемоизации функции
  const fetchCategories = useCallback(async () => {
    try {
      setLoading(true);
      let data;
      if (filter === 'all') {
        data = await getCategories();
      } else if (filter === 'Expense' || filter === 'Income') {
        data = await getCategoriesByType(filter);
      } else {
        data = await getCategories();
      }
      setCategories(data || []);
      setError('');
    } catch (err) {
      console.error('Ошибка загрузки категорий:', err);
      setError('Ошибка загрузки категорий. Проверьте подключение к серверу.');
      setCategories([]);
    } finally {
      setLoading(false);
    }
  }, [filter]);

  useEffect(() => {
    if (isAdmin()) {
      fetchCategories();
    }
  }, [fetchCategories, isAdmin]);

  const handleSubmit = async () => {
    if (!formData.name.trim()) {
      setError('Введите название категории');
      return;
    }

    if (formData.type !== 'Expense' && formData.type !== 'Income') {
      setError('Тип должен быть "Expense" или "Income"');
      return;
    }

    try {
      await createCategory(formData);
      setShowModal(false);
      setFormData({ name: '', icon: '💰', color: '#808080', type: 'Expense' });
      await fetchCategories();
    } catch (err) {
      console.error('Ошибка создания категории:', err);
      setError('Ошибка создания категории: ' + (err.message || 'Неизвестная ошибка'));
    }
  };

  const handleDelete = async (id, isSystem) => {
    if (isSystem) {
      alert('Системные категории нельзя удалить');
      return;
    }

    if (!window.confirm('Удалить эту категорию?')) return;
    
    try {
      await deleteCategory(id);
      await fetchCategories();
    } catch (err) {
      console.error('Ошибка удаления категории:', err);
      setError('Ошибка удаления категории: ' + (err.message || 'Неизвестная ошибка'));
    }
  };

  const filteredCategories = categories.filter(cat => {
    if (filter === 'all') return true;
    if (filter === 'expense') return cat.type === 'Expense';
    if (filter === 'income') return cat.type === 'Income';
    return cat.type === filter;
  });

  if (!isAdmin()) {
    return (
      <div className="container mt-4">
        <Alert variant="danger">Доступ запрещен. Только для администраторов.</Alert>
      </div>
    );
  }

  if (loading) {
    return (
      <div className="container mt-4 text-center">
        <div className="spinner-border" role="status">
          <span className="visually-hidden">Загрузка...</span>
        </div>
      </div>
    );
  }

  return (
    <div className="container mt-4">
      <div className="d-flex justify-content-between align-items-center mb-4">
        <h2>Управление категориями</h2>
        <Button variant="primary" onClick={() => setShowModal(true)}>
          + Новая категория
        </Button>
      </div>

      {/* Фильтры */}
      <div className="mb-4">
        <Button 
          variant={filter === 'all' ? 'primary' : 'outline-primary'} 
          className="me-2"
          onClick={() => setFilter('all')}
        >
          Все
        </Button>
        <Button 
          variant={filter === 'Expense' ? 'danger' : 'outline-danger'} 
          className="me-2"
          onClick={() => setFilter('Expense')}
        >
          Расходы
        </Button>
        <Button 
          variant={filter === 'Income' ? 'success' : 'outline-success'}
          onClick={() => setFilter('Income')}
        >
          Доходы
        </Button>
      </div>

      {error && <Alert variant="danger" onClose={() => setError('')} dismissible>{error}</Alert>}

      {filteredCategories.length === 0 ? (
        <Alert variant="info">
          Категории не найдены. Создайте первую категорию!
        </Alert>
      ) : (
        <Row>
          {filteredCategories.map(cat => (
            <Col md={4} key={cat.id} className="mb-3">
              <Card style={{ borderLeft: `5px solid ${cat.color || '#808080'}` }}>
                <Card.Body>
                  <div className="d-flex justify-content-between align-items-start">
                    <div>
                      <h4>
                        <span style={{ fontSize: '1.5em' }}>{cat.icon || '💰'}</span> {cat.name}
                      </h4>
                      <Badge bg={cat.type === 'Income' ? 'success' : 'secondary'} className="me-2">
                        {cat.type === 'Income' ? 'Доход' : 'Расход'}
                      </Badge>
                      {cat.isSystem && <Badge bg="info">Системная</Badge>}
                      <div className="mt-2 text-muted">
                        <small>Использований: {cat.usageCount || 0}</small>
                      </div>
                    </div>
                    {!cat.isSystem && (
                      <Button 
                        variant="outline-danger" 
                        size="sm"
                        onClick={() => handleDelete(cat.id, cat.isSystem)}
                      >
                        Удалить
                      </Button>
                    )}
                  </div>
                </Card.Body>
              </Card>
            </Col>
          ))}
        </Row>
      )}

      {/* Модальное окно для создания категории */}
      <Modal show={showModal} onHide={() => setShowModal(false)}>
        <Modal.Header closeButton>
          <Modal.Title>Новая категория</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <Form>
            <Form.Group className="mb-3">
              <Form.Label>Название *</Form.Label>
              <Form.Control
                type="text"
                placeholder="Например: Еда, Транспорт, Зарплата"
                value={formData.name}
                onChange={e => setFormData({...formData, name: e.target.value})}
                required
              />
            </Form.Group>

            <Form.Group className="mb-3">
              <Form.Label>Тип *</Form.Label>
              <div>
                <Button
                  variant={formData.type === 'Expense' ? 'danger' : 'outline-danger'}
                  className="me-2"
                  onClick={() => setFormData({...formData, type: 'Expense'})}
                >
                  Расход
                </Button>
                <Button
                  variant={formData.type === 'Income' ? 'success' : 'outline-success'}
                  onClick={() => setFormData({...formData, type: 'Income'})}
                >
                  Доход
                </Button>
              </div>
            </Form.Group>

            <Form.Group className="mb-3">
              <Form.Label>Иконка</Form.Label>
              <Form.Control
                type="text"
                placeholder="Эмодзи или символ"
                value={formData.icon}
                onChange={e => setFormData({...formData, icon: e.target.value})}
              />
              <Form.Text className="text-muted">
                Например: 🍔, 🚗, 💼, 🎁
              </Form.Text>
            </Form.Group>

            <Form.Group className="mb-3">
              <Form.Label>Цвет</Form.Label>
              <div className="d-flex align-items-center">
                <Form.Control
                  type="color"
                  value={formData.color}
                  onChange={e => setFormData({...formData, color: e.target.value})}
                  style={{ width: '50px', height: '38px', padding: '5px' }}
                  className="me-2"
                />
                <Form.Control
                  type="text"
                  value={formData.color}
                  onChange={e => setFormData({...formData, color: e.target.value})}
                  placeholder="#808080"
                />
              </div>
            </Form.Group>
          </Form>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={() => setShowModal(false)}>
            Отмена
          </Button>
          <Button variant="primary" onClick={handleSubmit}>
            Создать
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}
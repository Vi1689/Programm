import React, { useState, useEffect } from 'react';
import { 
  Table, Button, Alert, Badge, 
  Card, Row, Col, Modal, Form 
} from 'react-bootstrap';
import { useAuth } from '../context/AuthContext';
import { getAllUsers, updateUserRole, deleteUser, getAdminStats } from '../api/budgetApi';

export default function AdminUsers() {
  const [users, setUsers] = useState([]);
  const [sortedUsers, setSortedUsers] = useState([]);
  const [stats, setStats] = useState(null);
  const [showRoleModal, setShowRoleModal] = useState(false);
  const [selectedUser, setSelectedUser] = useState(null);
  const [newRole, setNewRole] = useState('');
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(true);
  const { user: currentUser } = useAuth();
  
  // Конфигурация сортировки
  const [sortConfig, setSortConfig] = useState({
    key: 'id',
    direction: 'asc'
  });

  useEffect(() => {
    fetchData();
  }, []);

  useEffect(() => {
    // Сортируем пользователей
    if (users.length === 0) {
      setSortedUsers([]);
      return;
    }

    const sorted = [...users].sort((a, b) => {
      let aValue, bValue;

      switch (sortConfig.key) {
        case 'id':
          aValue = a.id;
          bValue = b.id;
          break;
        case 'username':
          aValue = a.username.toLowerCase();
          bValue = b.username.toLowerCase();
          break;
        case 'email':
          aValue = a.email.toLowerCase();
          bValue = b.email.toLowerCase();
          break;
        case 'role':
          aValue = a.role.toLowerCase();
          bValue = b.role.toLowerCase();
          break;
        case 'createdAt':
          aValue = new Date(a.createdAt).getTime();
          bValue = new Date(b.createdAt).getTime();
          break;
        case 'transactionsCount':
          aValue = a.transactionsCount || 0;
          bValue = b.transactionsCount || 0;
          break;
        default:
          return 0;
      }

      if (aValue < bValue) {
        return sortConfig.direction === 'asc' ? -1 : 1;
      }
      if (aValue > bValue) {
        return sortConfig.direction === 'asc' ? 1 : -1;
      }
      return 0;
    });

    setSortedUsers(sorted);
  }, [users, sortConfig]);

  const fetchData = async () => {
    try {
      setLoading(true);
      const [usersData, statsData] = await Promise.all([
        getAllUsers(),
        getAdminStats()
      ]);
      
      // Преобразуем данные пользователей
    const usersWithTransactions = usersData.map(user => ({
      ...user,
      transactionsCount: user.transactionsCount || 0
    }));
      
      setUsers(usersWithTransactions);
      setStats(statsData);
      setError('');
    } catch (err) {
      console.error('Ошибка загрузки данных:', err);
      setError('Ошибка загрузки данных: ' + (err.message || 'Проверьте подключение к серверу'));
    } finally {
      setLoading(false);
    }
  };

  const handleSort = (key) => {
    setSortConfig(prevConfig => {
      // Если кликаем по тому же столбцу
      if (prevConfig.key === key) {
        // Меняем направление: asc -> desc -> asc
        if (prevConfig.direction === 'asc') {
          return { key, direction: 'desc' };
        } else if (prevConfig.direction === 'desc') {
          return { key, direction: 'asc' };
        }
      }
      // Если кликаем по другому столбцу, начинаем с asc
      return { key, direction: 'asc' };
    });
  };

  const getSortIcon = (key) => {
    if (sortConfig.key !== key) return '↕️';
    return sortConfig.direction === 'asc' ? '⬆️' : '⬇️';
  };

  const getSortTitle = (key) => {
    switch(key) {
      case 'id': return 'ID';
      case 'username': return 'Имя пользователя';
      case 'email': return 'Email';
      case 'role': return 'Роль';
      case 'createdAt': return 'Дата регистрации';
      case 'transactionsCount': return 'Транзакций';
      default: return '';
    }
  };

  const handleRoleUpdate = async (id, role) => {
    try {
      await updateUserRole(id, role);
      setShowRoleModal(false);
      await fetchData();
    } catch (err) {
      setError('Ошибка обновления роли: ' + (err.message || 'Неизвестная ошибка'));
    }
  };

  const handleDeleteUser = async (id) => {
    if (!window.confirm('Удалить этого пользователя?')) return;
    
    try {
      await deleteUser(id);
      await fetchData();
    } catch (err) {
      setError('Ошибка удаления пользователя: ' + (err.message || 'Неизвестная ошибка'));
    }
  };

  const formatDate = (dateString) => {
    return new Date(dateString).toLocaleDateString('ru-RU');
  };

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
      <h2 className="mb-4">
        Панель администратора <Badge bg="danger">Admin</Badge>
      </h2>

      {error && <Alert variant="danger" onClose={() => setError('')} dismissible>{error}</Alert>}

      {/* Статистика */}
      <Row className="mb-4">
        <Col md={3}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Пользователи</Card.Title>
              <h2>{stats?.totalUsers || 0}</h2>
            </Card.Body>
          </Card>
        </Col>
        <Col md={3}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Транзакции</Card.Title>
              <h2>{stats?.totalTransactions || 0}</h2>
            </Card.Body>
          </Card>
        </Col>
        <Col md={3}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Общий доход</Card.Title>
              <h3 className="text-success">{stats?.totalIncome?.toFixed(2) || '0.00'} ₽</h3>
            </Card.Body>
          </Card>
        </Col>
        <Col md={3}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Общие расходы</Card.Title>
              <h3 className="text-danger">{stats?.totalExpense?.toFixed(2) || '0.00'} ₽</h3>
            </Card.Body>
          </Card>
        </Col>
      </Row>

      {/* Список пользователей */}
      <Card>
        <Card.Body>
          <div className="d-flex justify-content-between align-items-center mb-3">
            <Card.Title className="mb-0">Пользователи системы</Card.Title>
            <small className="text-muted">
              Всего пользователей: {users.length}
            </small>
          </div>
          
          <div className="mb-3 p-2 bg-light rounded">
            <small className="text-muted">
              <strong>Текущая сортировка:</strong> {getSortTitle(sortConfig.key)} 
              {sortConfig.direction === 'asc' ? ' по возрастанию (⬆️)' : ' по убыванию (⬇️)'}. 
              Кликните на заголовок столбца для сортировки.
            </small>
          </div>
          
          <div className="table-responsive">
            <Table striped bordered hover>
              <thead>
                <tr>
                  <th 
                    style={{ 
                      cursor: 'pointer', 
                      userSelect: 'none',
                      whiteSpace: 'nowrap'
                    }}
                    onClick={() => handleSort('id')}
                  >
                    <div className="d-flex justify-content-between align-items-center">
                      <span>ID</span>
                      <span className="ms-3 fs-6">
                        {getSortIcon('id')}
                      </span>
                    </div>
                  </th>
                  <th 
                    style={{ 
                      cursor: 'pointer', 
                      userSelect: 'none',
                      whiteSpace: 'nowrap'
                    }}
                    onClick={() => handleSort('username')}
                  >
                    <div className="d-flex justify-content-between align-items-center">
                      <span>Имя пользователя</span>
                      <span className="ms-3 fs-6">
                        {getSortIcon('username')}
                      </span>
                    </div>
                  </th>
                  <th 
                    style={{ 
                      cursor: 'pointer', 
                      userSelect: 'none',
                      whiteSpace: 'nowrap'
                    }}
                    onClick={() => handleSort('email')}
                  >
                    <div className="d-flex justify-content-between align-items-center">
                      <span>Email</span>
                      <span className="ms-3 fs-6">
                        {getSortIcon('email')}
                      </span>
                    </div>
                  </th>
                  <th 
                    style={{ 
                      cursor: 'pointer', 
                      userSelect: 'none',
                      whiteSpace: 'nowrap'
                    }}
                    onClick={() => handleSort('role')}
                  >
                    <div className="d-flex justify-content-between align-items-center">
                      <span>Роль</span>
                      <span className="ms-3 fs-6">
                        {getSortIcon('role')}
                      </span>
                    </div>
                  </th>
                  <th 
                    style={{ 
                      cursor: 'pointer', 
                      userSelect: 'none',
                      whiteSpace: 'nowrap'
                    }}
                    onClick={() => handleSort('createdAt')}
                  >
                    <div className="d-flex justify-content-between align-items-center">
                      <span>Дата регистрации</span>
                      <span className="ms-3 fs-6">
                        {getSortIcon('createdAt')}
                      </span>
                    </div>
                  </th>
                  <th 
                    style={{ 
                      cursor: 'pointer', 
                      userSelect: 'none',
                      whiteSpace: 'nowrap'
                    }}
                    onClick={() => handleSort('transactionsCount')}
                  >
                    <div className="d-flex justify-content-between align-items-center">
                      <span>Транзакций</span>
                      <span className="ms-3 fs-6">
                        {getSortIcon('transactionsCount')}
                      </span>
                    </div>
                  </th>
                  <th style={{ whiteSpace: 'nowrap' }}>Действия</th>
                </tr>
              </thead>
              <tbody>
                {sortedUsers.map(u => (
                  <tr key={u.id}>
                    <td><strong>{u.id}</strong></td>
                    <td>{u.username}</td>
                    <td>
                      <a href={`mailto:${u.email}`} className="text-decoration-none">
                        {u.email}
                      </a>
                    </td>
                    <td>
                      <Badge bg={u.role === 'Admin' ? 'danger' : 'secondary'}>
                        {u.role === 'Admin' ? 'Админ' : 'Пользователь'}
                      </Badge>
                    </td>
                    <td>{formatDate(u.createdAt)}</td>
                    <td>
                      <div className="d-flex align-items-center">
                        <Badge bg={u.transactionsCount > 0 ? 'primary' : 'secondary'} className="me-2">
                          {u.transactionsCount}
                        </Badge>
                        {u.transactionsCount > 0 && (
                          <small className="text-muted">
                            ({((u.transactionsCount / stats?.totalTransactions) * 100 || 0).toFixed(1)}%)
                          </small>
                        )}
                      </div>
                    </td>
                    <td>
                      <div className="d-flex flex-wrap gap-1">
                        <Button 
                          variant="outline-primary" 
                          size="sm"
                          onClick={() => {
                            setSelectedUser(u);
                            setNewRole(u.role);
                            setShowRoleModal(true);
                          }}
                          disabled={u.id === currentUser?.userId}
                          title="Изменить роль"
                        >
                          Роль
                        </Button>
                        <Button 
                          variant="outline-danger" 
                          size="sm"
                          onClick={() => handleDeleteUser(u.id)}
                          disabled={u.id === currentUser?.userId || u.role === 'Admin'}
                          title="Удалить пользователя"
                        >
                          Удалить
                        </Button>
                      </div>
                    </td>
                  </tr>
                ))}
              </tbody>
            </Table>
          </div>
        </Card.Body>
      </Card>

      {/* Модальное окно изменения роли */}
      <Modal show={showRoleModal} onHide={() => setShowRoleModal(false)}>
        <Modal.Header closeButton>
          <Modal.Title>Изменение роли пользователя</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          {selectedUser && (
            <>
              <div className="mb-3">
                <p><strong>ID:</strong> {selectedUser.id}</p>
                <p><strong>Имя пользователя:</strong> {selectedUser.username}</p>
                <p><strong>Email:</strong> {selectedUser.email}</p>
                <p>
                  <strong>Текущая роль:</strong> 
                  <Badge bg={selectedUser.role === 'Admin' ? 'danger' : 'secondary'} className="ms-2">
                    {selectedUser.role === 'Admin' ? 'Админ' : 'Пользователь'}
                  </Badge>
                </p>
                <p><strong>Транзакций:</strong> {selectedUser.transactionsCount}</p>
                <p><strong>Дата регистрации:</strong> {formatDate(selectedUser.createdAt)}</p>
              </div>
              
              <hr />
              
              <Form.Group>
                <Form.Label><strong>Выберите новую роль:</strong></Form.Label>
                <div className="d-grid gap-2">
                  <Button
                    variant={newRole === 'User' ? 'secondary' : 'outline-secondary'}
                    size="lg"
                    onClick={() => setNewRole('User')}
                  >
                    👤 Пользователь
                  </Button>
                  <Button
                    variant={newRole === 'Admin' ? 'danger' : 'outline-danger'}
                    size="lg"
                    onClick={() => setNewRole('Admin')}
                  >
                    👑 Администратор
                  </Button>
                </div>
              </Form.Group>
            </>
          )}
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={() => setShowRoleModal(false)}>
            Отмена
          </Button>
          <Button 
            variant="primary" 
            onClick={() => handleRoleUpdate(selectedUser.id, newRole)}
            disabled={!selectedUser || selectedUser.role === newRole}
          >
            Сохранить изменения
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}
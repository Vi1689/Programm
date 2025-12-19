import React, { useState, useEffect } from 'react';
import { 
  Table, Button, Alert, Badge, 
  Card, Row, Col, Modal, Form 
} from 'react-bootstrap';
import { useAuth } from '../context/AuthContext';
import { getAllUsers, updateUserRole, deleteUser, getAdminStats } from '../api/budgetApi';

export default function AdminUsers() {
  const [users, setUsers] = useState([]);
  const [stats, setStats] = useState(null);
  const [showRoleModal, setShowRoleModal] = useState(false);
  const [selectedUser, setSelectedUser] = useState(null);
  const [newRole, setNewRole] = useState('');
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(true);
  const { user: currentUser } = useAuth();

  useEffect(() => {
    fetchData();
  }, []);

  const fetchData = async () => {
    try {
      setLoading(true);
      const [usersData, statsData] = await Promise.all([
        getAllUsers(),
        getAdminStats()
      ]);
      setUsers(usersData);
      setStats(statsData);
      setError('');
    } catch (err) {
      setError('Ошибка загрузки данных');
    } finally {
      setLoading(false);
    }
  };

  const handleRoleUpdate = async (id, role) => {
    try {
      await updateUserRole(id, role);
      setShowRoleModal(false);
      fetchData();
    } catch (err) {
      setError('Ошибка обновления роли');
    }
  };

  const handleDeleteUser = async (id) => {
    if (!window.confirm('Удалить этого пользователя?')) return;
    
    try {
      await deleteUser(id);
      fetchData();
    } catch (err) {
      setError('Ошибка удаления пользователя');
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
              <h3 className="text-success">₽{stats?.totalIncome?.toFixed(2) || '0.00'}</h3>
            </Card.Body>
          </Card>
        </Col>
        <Col md={3}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Общие расходы</Card.Title>
              <h3 className="text-danger">₽{stats?.totalExpense?.toFixed(2) || '0.00'}</h3>
            </Card.Body>
          </Card>
        </Col>
      </Row>

      {/* Список пользователей */}
      <Card>
        <Card.Body>
          <Card.Title>Пользователи системы</Card.Title>
          <Table striped bordered hover responsive>
            <thead>
              <tr>
                <th>ID</th>
                <th>Имя пользователя</th>
                <th>Email</th>
                <th>Роль</th>
                <th>Дата регистрации</th>
                <th>Транзакций</th>
                <th>Действия</th>
              </tr>
            </thead>
            <tbody>
              {users.map(u => (
                <tr key={u.id}>
                  <td>{u.id}</td>
                  <td>{u.username}</td>
                  <td>{u.email}</td>
                  <td>
                    <Badge bg={u.role === 'Admin' ? 'danger' : 'secondary'}>
                      {u.role}
                    </Badge>
                  </td>
                  <td>{formatDate(u.createdAt)}</td>
                  <td>{u.transactions?.length || 0}</td>
                  <td>
                    <Button 
                      variant="outline-primary" 
                      size="sm" 
                      className="me-2"
                      onClick={() => {
                        setSelectedUser(u);
                        setNewRole(u.role);
                        setShowRoleModal(true);
                      }}
                      disabled={u.id === currentUser?.userId}
                    >
                      Роль
                    </Button>
                    <Button 
                      variant="outline-danger" 
                      size="sm"
                      onClick={() => handleDeleteUser(u.id)}
                      disabled={u.id === currentUser?.userId || u.role === 'Admin'}
                    >
                      Удалить
                    </Button>
                  </td>
                </tr>
              ))}
            </tbody>
          </Table>
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
              <p>Пользователь: <strong>{selectedUser.username}</strong></p>
              <p>Текущая роль: <Badge bg={selectedUser.role === 'Admin' ? 'danger' : 'secondary'}>{selectedUser.role}</Badge></p>
              
              <Form.Group className="mt-3">
                <Form.Label>Новая роль:</Form.Label>
                <div>
                  <Button
                    variant={newRole === 'User' ? 'secondary' : 'outline-secondary'}
                    className="me-2"
                    onClick={() => setNewRole('User')}
                  >
                    User
                  </Button>
                  <Button
                    variant={newRole === 'Admin' ? 'danger' : 'outline-danger'}
                    onClick={() => setNewRole('Admin')}
                  >
                    Admin
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
            Сохранить
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}
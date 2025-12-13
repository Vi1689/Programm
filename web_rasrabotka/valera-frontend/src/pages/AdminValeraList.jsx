import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { getAllValeras, deleteValera } from '../api/valeraApi';
import { Button, Table, InputGroup, FormControl, Alert, Badge } from 'react-bootstrap';

export default function AdminValeraList() {
  const [valeras, setValeras] = useState([]);
  const [search, setSearch] = useState('');
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(true);
  const navigate = useNavigate();

  useEffect(() => {
    fetchValeras();
  }, []);

  const fetchValeras = async () => {
    try {
      setLoading(true);
      const data = await getAllValeras();
      setValeras(data);
      setError('');
    } catch (err) {
      setError('Ошибка загрузки данных. Возможно, у вас нет прав администратора.');
    } finally {
      setLoading(false);
    }
  };

  const handleDelete = async (id) => {
    if (!window.confirm('Удалить эту Валеру?')) return;
    
    try {
      await deleteValera(id);
      fetchValeras();
    } catch (err) {
      setError('Ошибка удаления');
    }
  };

  const filteredValeras = valeras.filter(v => 
    v.name.toLowerCase().includes(search.toLowerCase()) ||
    v.userId.toString().includes(search)
  );

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
      <h2>
        Все Валеры <Badge bg="danger">Администратор</Badge>
      </h2>
      <p className="text-muted">Всего Валер в системе: {valeras.length}</p>
      
      {error && <Alert variant="danger" onClose={() => setError('')} dismissible>{error}</Alert>}

      <InputGroup className="mb-3">
        <FormControl
          placeholder="Поиск по имени или User ID"
          value={search}
          onChange={e => setSearch(e.target.value)}
        />
      </InputGroup>

      {filteredValeras.length === 0 ? (
        <Alert variant="info">Валеры не найдены</Alert>
      ) : (
        <Table striped bordered hover responsive>
          <thead>
            <tr>
              <th>ID</th>
              <th>User ID</th>
              <th>Имя</th>
              <th>Health</th>
              <th>Mana</th>
              <th>Cheerfulness</th>
              <th>Fatigue</th>
              <th>Money</th>
              <th>Действия</th>
            </tr>
          </thead>
          <tbody>
            {filteredValeras.map(v => (
              <tr key={v.id}>
                <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>
                  {v.id}
                </td>
                <td>
                  <Badge bg="secondary">{v.userId}</Badge>
                </td>
                <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>
                  {v.name}
                </td>
                <td>{v.health}</td>
                <td>{v.mana}</td>
                <td>{v.cheerfulness}</td>
                <td>{v.fatigue}</td>
                <td>{v.money}</td>
                <td>
                  <Button 
                    variant="primary" 
                    size="sm" 
                    className="me-2"
                    onClick={() => navigate(`/valera/${v.id}`)}
                  >
                    Открыть
                  </Button>
                  <Button 
                    variant="danger" 
                    size="sm" 
                    onClick={() => handleDelete(v.id)}
                  >
                    Удалить
                  </Button>
                </td>
              </tr>
            ))}
          </tbody>
        </Table>
      )}
    </div>
  );
}
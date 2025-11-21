import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { getAllValeras, createValera } from '../api/valeraApi';
import { Button, Table, Modal, Form, InputGroup, FormControl } from 'react-bootstrap';

export default function ValeraList() {
  const [valeras, setValeras] = useState([]);
  const [showModal, setShowModal] = useState(false);
  const [newValera, setNewValera] = useState({ name: '', health: 100, mana: 0, cheerfulness: 0, fatigue: 0, money: 0 });
  const [search, setSearch] = useState('');
  const navigate = useNavigate();

  useEffect(() => {
    fetchValeras();
  }, []);

  const fetchValeras = async () => {
    const data = await getAllValeras();
    setValeras(data);
  };

  const handleCreate = async () => {
    if (!newValera.name.trim()) {
      alert("Имя Валеры не может быть пустым");
      return;
    }
    await createValera(newValera);
    setShowModal(false);
    setNewValera({ name: '', health: 100, mana: 0, cheerfulness: 0, fatigue: 0, money: 0 });
    fetchValeras();
  };

  const handleDelete = async (id) => {
    try {
      await fetch(`http://localhost:5097/api/valera/${id}`, { method: 'DELETE' });
      fetchValeras();
    } catch (err) {
      console.error(err);
    }
  };

  const filteredValeras = valeras.filter(v => v.name.toLowerCase().includes(search.toLowerCase()));

  return (
    <div className="container mt-4">
      <h2>Список Валер</h2>

      <InputGroup className="mb-3">
        <FormControl
          placeholder="Поиск по имени"
          value={search}
          onChange={e => setSearch(e.target.value)}
        />
        <Button variant="primary" onClick={() => setShowModal(true)}>Создать Валеру</Button>
      </InputGroup>

      <Table striped bordered hover>
        <thead>
          <tr>
            <th>ID</th>
            <th>Имя</th>
            <th>Health</th>
            <th>Mana</th>
            <th>Cheerfulness</th>
            <th>Fatigue</th>
            <th>Money</th>
            <th>Действие</th>
          </tr>
        </thead>
        <tbody>
          {filteredValeras.map(v => (
            <tr key={v.id}>
              <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>{v.id}</td>
              <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>{v.name}</td>
              <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>{v.health}</td>
              <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>{v.mana}</td>
              <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>{v.cheerfulness}</td>
              <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>{v.fatigue}</td>
              <td style={{cursor: 'pointer'}} onClick={() => navigate(`/valera/${v.id}`)}>{v.money}</td>
              <td>
                <Button variant="danger" size="sm" onClick={() => handleDelete(v.id)}>Удалить</Button>
              </td>
            </tr>
          ))}
        </tbody>
      </Table>

      <Modal show={showModal} onHide={() => setShowModal(false)}>
        <Modal.Header closeButton>
          <Modal.Title>Создать Валеру</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <Form>
            <Form.Group className="mb-2">
              <Form.Label>Имя</Form.Label>
              <Form.Control
                type="text"
                value={newValera.name}
                onChange={e => setNewValera({...newValera, name: e.target.value})}
              />
            </Form.Group>
            {Object.keys(newValera).filter(k => k !== 'name').map(key => (
              <Form.Group key={key} className="mb-2">
                <Form.Label>{key}</Form.Label>
                <Form.Control
                  type="number"
                  value={newValera[key]}
                  onChange={e => setNewValera({...newValera, [key]: Number(e.target.value)})}
                />
              </Form.Group>
            ))}
          </Form>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={() => setShowModal(false)}>Отмена</Button>
          <Button variant="primary" onClick={handleCreate}>Создать</Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}

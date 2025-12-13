import React, { useState, useEffect } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import { getValera, action } from '../api/valeraApi';
import { Button, ProgressBar, Card, Alert, Badge } from 'react-bootstrap';
import { useAuth } from '../context/AuthContext';

export default function ValeraStats() {
  const { id } = useParams();
  const [valera, setValera] = useState(null);
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(true);
  const [actionLoading, setActionLoading] = useState(false);
  const navigate = useNavigate();
  const { user, isAdmin } = useAuth();

  useEffect(() => {
    fetchValera();
  }, [id]);

  const fetchValera = async () => {
    try {
      setLoading(true);
      const data = await getValera(id);
      setValera(data);
      setError('');
    } catch (err) {
      setError('Ошибка загрузки данных или доступ запрещен');
    } finally {
      setLoading(false);
    }
  };

  const handleAction = async (act) => {
    try {
      setActionLoading(true);
      await action(id, act);
      await fetchValera();
      setError('');
    } catch (err) {
      setError('Ошибка выполнения действия: ' + err.message);
    } finally {
      setActionLoading(false);
    }
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

  if (error && !valera) {
    return (
      <div className="container mt-4">
        <Alert variant="danger">{error}</Alert>
        <Button onClick={() => navigate(-1)}>Назад</Button>
      </div>
    );
  }

  if (!valera) return null;

  const canEdit = isAdmin() || valera.userId === user?.userId;

  return (
    <div className="container mt-4">
      <Button variant="secondary" onClick={() => navigate(-1)} className="mb-3">
        ← Назад
      </Button>

      <div className="d-flex justify-content-between align-items-center mb-3">
        <h2>{valera.name}</h2>
        {isAdmin() && <Badge bg="danger">Режим администратора</Badge>}
      </div>
      
      {!canEdit && (
        <Alert variant="warning">
          Вы не можете управлять этой Валерой (владелец: User ID {valera.userId})
        </Alert>
      )}

      {error && <Alert variant="danger" onClose={() => setError('')} dismissible>{error}</Alert>}
      
      <Card className="p-3 mb-3">
        <div className="mb-3">
          <strong>ID:</strong> {valera.id} | <strong>Владелец:</strong> User ID {valera.userId}
        </div>

        <div className="mb-2">
          <strong>Health:</strong>
          <ProgressBar 
            now={valera.health} 
            label={`${valera.health}/100`}
            variant={valera.health > 50 ? 'success' : valera.health > 20 ? 'warning' : 'danger'}
          />
        </div>

        <div className="mb-2">
          <strong>Mana (Алкоголь):</strong>
          <ProgressBar 
            now={valera.mana} 
            label={`${valera.mana}/100`}
            variant={valera.mana < 50 ? 'info' : 'danger'}
          />
        </div>

        <div className="mb-2">
          <strong>Cheerfulness (Настроение):</strong>
          <ProgressBar 
            now={(valera.cheerfulness + 10) * 5} 
            max={100}
            label={`${valera.cheerfulness}/10`}
            variant={valera.cheerfulness > 0 ? 'success' : 'warning'}
          />
        </div>

        <div className="mb-2">
          <strong>Fatigue (Усталость):</strong>
          <ProgressBar 
            now={valera.fatigue} 
            label={`${valera.fatigue}/100`}
            variant={valera.fatigue < 50 ? 'success' : valera.fatigue < 80 ? 'warning' : 'danger'}
          />
        </div>

        <div className="mt-3">
          <h4>💰 Деньги: {valera.money} руб.</h4>
        </div>
      </Card>

      {canEdit && (
        <>
          <h4>Действия:</h4>
          <div className="d-flex flex-wrap gap-2">
            <Button 
              variant="primary"
              onClick={() => handleAction('work')} 
              disabled={valera.mana >= 50 || valera.fatigue >= 10 || actionLoading}
            >
              💼 Пойти на работу
            </Button>
            <Button 
              variant="success"
              onClick={() => handleAction('nature')}
              disabled={actionLoading}
            >
              🌳 Созерцать природу
            </Button>
            <Button 
              variant="warning"
              onClick={() => handleAction('wine')}
              disabled={actionLoading}
            >
              🍷 Пить вино и смотреть сериал
            </Button>
            <Button 
              variant="info"
              onClick={() => handleAction('bar')}
              disabled={actionLoading}
            >
              🍺 Сходить в бар
            </Button>
            <Button 
              variant="danger"
              onClick={() => handleAction('marginals')}
              disabled={actionLoading}
            >
              🥃 Выпить с маргиналами
            </Button>
            <Button 
              variant="secondary"
              onClick={() => handleAction('metro')}
              disabled={actionLoading}
            >
              🎵 Петь в метро
            </Button>
            <Button 
              variant="dark"
              onClick={() => handleAction('sleep')}
              disabled={actionLoading}
            >
              😴 Спать
            </Button>
          </div>

          {actionLoading && (
            <div className="mt-3">
              <div className="spinner-border spinner-border-sm me-2" role="status"></div>
              Выполнение действия...
            </div>
          )}

          <Alert variant="info" className="mt-3">
            <strong>Подсказки:</strong>
            <ul className="mb-0 mt-2">
              <li>Работать можно только при Mana &lt; 50 и Fatigue &lt; 10</li>
              <li>Сон восстанавливает здоровье при низком Mana</li>
              <li>Следите за балансом показателей!</li>
            </ul>
          </Alert>
        </>
      )}
    </div>
  );
}
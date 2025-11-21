import React, { useState, useEffect } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import { getValera, action } from '../api/valeraApi';
import { Button, ProgressBar, Card } from 'react-bootstrap';

export default function ValeraStats() {
  const { id } = useParams();
  const [valera, setValera] = useState(null);
  const navigate = useNavigate();

  useEffect(() => {
    fetchValera();
  }, []);

  const fetchValera = async () => {
    const data = await getValera(id);
    setValera(data);
  };

  const handleAction = async (act) => {
    await action(id, act);
    fetchValera();
  };

  if (!valera) return <div className="container mt-4">Загрузка...</div>;

  return (
    <div className="container mt-4">
      <Button variant="secondary" onClick={() => navigate(-1)}>Назад</Button>
      <h2 className="mt-3">Валера {valera.id}</h2>
      <Card className="p-3 mb-3">
        <p>Health: <ProgressBar now={valera.health} label={valera.health} /></p>
        <p>Mana: <ProgressBar now={valera.mana} label={valera.mana} /></p>
        <p>Cheerfulness: <ProgressBar now={valera.cheerfulness + 10} max={20} label={valera.cheerfulness} /></p>
        <p>Fatigue: <ProgressBar now={valera.fatigue} label={valera.fatigue} /></p>
        <p>Money: {valera.money}</p>
      </Card>

      <div className="d-flex flex-wrap gap-2">
        <Button onClick={() => handleAction('work')} disabled={valera.mana >= 50 || valera.fatigue >= 10}>Пойти на работу</Button>
        <Button onClick={() => handleAction('nature')}>Созерцать природу</Button>
        <Button onClick={() => handleAction('wine')}>Пить вино и смотреть сериал</Button>
        <Button onClick={() => handleAction('bar')}>Сходить в бар</Button>
        <Button onClick={() => handleAction('marginals')}>Выпить с маргинальными личностями</Button>
        <Button onClick={() => handleAction('metro')}>Петь в метро</Button>
        <Button onClick={() => handleAction('sleep')}>Спать</Button>
      </div>
    </div>
  );
}

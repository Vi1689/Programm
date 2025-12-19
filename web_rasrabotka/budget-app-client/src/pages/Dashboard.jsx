import React, { useState, useEffect } from 'react';
import { Card, Row, Col, Alert } from 'react-bootstrap';
import { getStats, getPopularCategories } from '../api/budgetApi';
import { Doughnut, Bar } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  ArcElement,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend
} from 'chart.js';

ChartJS.register(
  ArcElement,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend
);

export default function Dashboard() {
  const [stats, setStats] = useState(null);
  const [popularCategories, setPopularCategories] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState('');

  useEffect(() => {
    fetchData();
  }, []);

  const fetchData = async () => {
    try {
      setLoading(true);
      const [statsData, popularData] = await Promise.all([
        getStats(),
        getPopularCategories()
      ]);
      setStats(statsData);
      setPopularCategories(popularData);
      setError('');
    } catch (err) {
      console.error('Ошибка загрузки данных:', err);
      setError('Ошибка загрузки данных. Проверьте подключение к серверу.');
    } finally {
      setLoading(false);
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

  const doughnutData = {
    labels: stats?.categoryStats.map(c => c.category) || [],
    datasets: [
      {
        label: 'Расходы по категориям',
        data: stats?.categoryStats.map(c => c.amount) || [],
        backgroundColor: stats?.categoryStats.map(c => c.color) || [],
        borderWidth: 1
      }
    ]
  };

  const monthlyData = {
    labels: stats?.monthlyStats.map(m => m.month) || [],
    datasets: [
      {
        label: 'Доходы',
        data: stats?.monthlyStats.map(m => m.income) || [],
        backgroundColor: 'rgba(46, 204, 113, 0.5)',
        borderColor: 'rgba(46, 204, 113, 1)',
        borderWidth: 1
      },
      {
        label: 'Расходы',
        data: stats?.monthlyStats.map(m => m.expense) || [],
        backgroundColor: 'rgba(231, 76, 60, 0.5)',
        borderColor: 'rgba(231, 76, 60, 1)',
        borderWidth: 1
      }
    ]
  };

  return (
    <div className="container mt-4">
      <h2>Панель управления бюджетом</h2>
      
      {error && <Alert variant="danger">{error}</Alert>}
      
      {/* Карточки с общей статистикой */}
      <Row className="mt-4">
        <Col md={4}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Общий доход</Card.Title>
              <h3 className="text-success">{stats?.totalIncome?.toFixed(2) || '0.00'} ₽</h3>
            </Card.Body>
          </Card>
        </Col>
        <Col md={4}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Общие расходы</Card.Title>
              <h3 className="text-danger">{stats?.totalExpense?.toFixed(2) || '0.00'} ₽</h3>
            </Card.Body>
          </Card>
        </Col>
        <Col md={4}>
          <Card className="text-center">
            <Card.Body>
              <Card.Title>Баланс</Card.Title>
              <h3 className={stats?.balance >= 0 ? 'text-success' : 'text-danger'}>
                {stats?.balance?.toFixed(2) || '0.00'} ₽
              </h3>
            </Card.Body>
          </Card>
        </Col>
      </Row>

      {/* Графики */}
      <Row className="mt-4">
        <Col md={6}>
          <Card>
            <Card.Body>
              <Card.Title>Распределение расходов</Card.Title>
              <div style={{ height: '300px' }}>
                {stats?.categoryStats && stats.categoryStats.length > 0 ? (
                  <Doughnut data={doughnutData} options={{ maintainAspectRatio: false }} />
                ) : (
                  <p className="text-center text-muted mt-5">Нет данных о расходах</p>
                )}
              </div>
            </Card.Body>
          </Card>
        </Col>
        <Col md={6}>
          <Card>
            <Card.Body>
              <Card.Title>Динамика по месяцам</Card.Title>
              <div style={{ height: '300px' }}>
                {stats?.monthlyStats && stats.monthlyStats.length > 0 ? (
                  <Bar data={monthlyData} options={{ maintainAspectRatio: false }} />
                ) : (
                  <p className="text-center text-muted mt-5">Нет данных за месяцы</p>
                )}
              </div>
            </Card.Body>
          </Card>
        </Col>
      </Row>

      {/* Популярные категории */}
      <Card className="mt-4">
        <Card.Body>
          <Card.Title>Популярные категории</Card.Title>
          {popularCategories.length === 0 ? (
            <p className="text-center text-muted">Нет популярных категорий</p>
          ) : (
            <Row>
              {popularCategories.map((cat, index) => (
                <Col md={3} key={cat.name} className="mb-3">
                  <Card style={{ borderLeft: `5px solid ${cat.color}` }}>
                    <Card.Body>
                      <div className="d-flex justify-content-between">
                        <div>
                          <h5>{cat.icon} {cat.name}</h5>
                          <span className={`badge ${cat.type === 'Income' ? 'bg-success' : 'bg-secondary'}`}>
                            {cat.type === 'Income' ? 'Доход' : 'Расход'}
                          </span>
                        </div>
                        <div className="text-end">
                          <h6>{cat.usageCount}</h6>
                          <small>использований</small>
                        </div>
                      </div>
                    </Card.Body>
                  </Card>
                </Col>
              ))}
            </Row>
          )}
        </Card.Body>
      </Card>
    </div>
  );
}
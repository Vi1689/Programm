import React, { useState, useEffect } from 'react';
import { 
  Table, Button, Modal, Form, Alert, 
  InputGroup, FormControl, Badge, Dropdown 
} from 'react-bootstrap';
import { 
  getMyTransactions, createTransaction, 
  updateTransaction, deleteTransaction 
} from '../api/budgetApi';
import { getCategories } from '../api/budgetApi';

export default function Transactions() {
  const [transactions, setTransactions] = useState([]);
  const [sortedTransactions, setSortedTransactions] = useState([]);
  const [showModal, setShowModal] = useState(false);
  const [editingTransaction, setEditingTransaction] = useState(null);
  const [formData, setFormData] = useState({
    amount: '',
    category: '',
    description: '',
    isIncome: false,
    categoryColor: '#808080',
    categoryIcon: '💰'
  });
  const [categories, setCategories] = useState([]);
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(true);
  const [typeFilter, setTypeFilter] = useState('all'); // all, income, expense
  const [sortConfig, setSortConfig] = useState({
    key: 'date',
    direction: 'desc' // asc, desc
  });

  useEffect(() => {
    fetchTransactions();
    fetchAllCategories();
  }, []);

  useEffect(() => {
    // Сортируем транзакции при изменении сортировки или фильтра
    let filtered = transactions.filter(t => {
      if (typeFilter === 'all') return true;
      if (typeFilter === 'income') return t.isIncome;
      if (typeFilter === 'expense') return !t.isIncome;
      return true;
    });

    // Применяем сортировку
    filtered.sort((a, b) => {
      let aValue, bValue;

      switch (sortConfig.key) {
        case 'date':
          aValue = new Date(a.date).getTime();
          bValue = new Date(b.date).getTime();
          break;
        case 'category':
          aValue = a.category.toLowerCase();
          bValue = b.category.toLowerCase();
          break;
        case 'description':
          aValue = (a.description || '').toLowerCase();
          bValue = (b.description || '').toLowerCase();
          break;
        case 'amount':
          aValue = a.amount;
          bValue = b.amount;
          break;
        case 'type':
          aValue = a.isIncome ? 1 : 0;
          bValue = b.isIncome ? 1 : 0;
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

    setSortedTransactions(filtered);
  }, [transactions, typeFilter, sortConfig]);

  const fetchTransactions = async () => {
    try {
      setLoading(true);
      const data = await getMyTransactions();
      setTransactions(data);
      setError('');
    } catch (err) {
      console.error('Ошибка загрузки транзакций:', err);
      setError('Ошибка загрузки транзакций. Проверьте подключение к серверу.');
    } finally {
      setLoading(false);
    }
  };

  const fetchAllCategories = async () => {
    try {
      const data = await getCategories();
      setCategories(data || []);
    } catch (err) {
      console.error('Ошибка загрузки категорий:', err);
    }
  };

  const handleSort = (key) => {
    setSortConfig(prevConfig => {
      // Если кликаем по тому же столбцу
      if (prevConfig.key === key) {
        // Меняем направление: desc -> asc -> desc
        if (prevConfig.direction === 'desc') {
          return { key, direction: 'asc' };
        } else if (prevConfig.direction === 'asc') {
          // Если уже asc и кликаем еще раз, остаемся на asc
          // Или можно вернуть к исходной сортировке по дате
          return { key, direction: 'desc' };
        }
      }
      // Если кликаем по другому столбцу, начинаем с desc
      return { key, direction: 'desc' };
    });
  };

  const handleSubmit = async () => {
    if (!formData.amount || !formData.category) {
      setError('Заполните все обязательные поля');
      return;
    }

    const amountValue = parseFloat(formData.amount);
    if (isNaN(amountValue) || amountValue <= 0) {
      setError('Введите корректную сумму (больше 0)');
      return;
    }

    try {
      const dataToSend = {
        ...formData,
        amount: amountValue
      };

      if (editingTransaction) {
        await updateTransaction(editingTransaction.id, dataToSend);
      } else {
        await createTransaction(dataToSend);
      }

      setShowModal(false);
      setFormData({ 
        amount: '', 
        category: '', 
        description: '', 
        isIncome: false,
        categoryColor: '#808080',
        categoryIcon: '💰'
      });
      setEditingTransaction(null);
      await fetchTransactions();
    } catch (err) {
      console.error('Ошибка сохранения транзакции:', err);
      setError('Ошибка сохранения транзакции: ' + (err.message || 'Неизвестная ошибка'));
    }
  };

  const handleDelete = async (id) => {
    if (!window.confirm('Удалить эту транзакцию?')) return;
    
    try {
      await deleteTransaction(id);
      await fetchTransactions();
    } catch (err) {
      console.error('Ошибка удаления транзакции:', err);
      setError('Ошибка удаления транзакции: ' + (err.message || 'Неизвестная ошибка'));
    }
  };

  const handleEdit = (transaction) => {
    setEditingTransaction(transaction);
    setFormData({
      amount: transaction.amount.toString(),
      category: transaction.category,
      description: transaction.description || '',
      isIncome: transaction.isIncome,
      categoryColor: transaction.categoryColor || '#808080',
      categoryIcon: transaction.categoryIcon || '💰'
    });
    setShowModal(true);
  };

  const handleCategoryChange = (categoryName) => {
    const selectedCategory = categories.find(c => c.name === categoryName);
    if (selectedCategory) {
      setFormData({
        ...formData,
        category: categoryName,
        categoryColor: selectedCategory.color,
        categoryIcon: selectedCategory.icon
      });
    } else {
      setFormData({
        ...formData,
        category: categoryName,
        categoryColor: '#808080',
        categoryIcon: '💰'
      });
    }
  };

  const formatDate = (dateString) => {
    return new Date(dateString).toLocaleDateString('ru-RU', {
      day: '2-digit',
      month: '2-digit',
      year: 'numeric',
      hour: '2-digit',
      minute: '2-digit'
    });
  };

  // Получение категорий для выпадающего списка
  const expenseCategories = categories.filter(c => c.type === 'Expense');
  const incomeCategories = categories.filter(c => c.type === 'Income');
  const availableCategories = formData.isIncome ? incomeCategories : expenseCategories;

  // Функция для отображения значка сортировки
  const getSortIcon = (key) => {
    if (sortConfig.key !== key) return '↕️';
    return sortConfig.direction === 'asc' ? '⬆️' : '⬇️';
  };

  // Получение текстового описания текущей сортировки
  const getSortText = (key) => {
    if (sortConfig.key !== key) return '';
    return sortConfig.direction === 'asc' ? ' (возрастание)' : ' (убывание)';
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
      <div className="d-flex justify-content-between align-items-center mb-4">
        <h2>Мои транзакции</h2>
        <Button variant="primary" onClick={() => setShowModal(true)}>
          + Добавить транзакцию
        </Button>
      </div>

      {/* Фильтры и сортировка */}
      <div className="d-flex justify-content-between align-items-center mb-3">
        <div>
          <Button 
            variant={typeFilter === 'all' ? 'primary' : 'outline-primary'} 
            className="me-2"
            onClick={() => setTypeFilter('all')}
          >
            Все
          </Button>
          <Button 
            variant={typeFilter === 'income' ? 'success' : 'outline-success'} 
            className="me-2"
            onClick={() => setTypeFilter('income')}
          >
            Доходы
          </Button>
          <Button 
            variant={typeFilter === 'expense' ? 'danger' : 'outline-danger'}
            onClick={() => setTypeFilter('expense')}
          >
            Расходы
          </Button>
        </div>
        
        <div className="d-flex align-items-center">
          <span className="me-2 text-muted">Сортировка:</span>
          <Dropdown>
            <Dropdown.Toggle variant="outline-secondary" size="sm">
              {sortConfig.key === 'date' ? 'Дата' : 
               sortConfig.key === 'category' ? 'Категория' :
               sortConfig.key === 'amount' ? 'Сумма' :
               sortConfig.key === 'type' ? 'Тип' : 'Описание'}
              {getSortIcon(sortConfig.key)}
            </Dropdown.Toggle>
            <Dropdown.Menu>
              <Dropdown.Item onClick={() => handleSort('date')}>
                Дата {getSortIcon('date')}
              </Dropdown.Item>
              <Dropdown.Item onClick={() => handleSort('category')}>
                Категория {getSortIcon('category')}
              </Dropdown.Item>
              <Dropdown.Item onClick={() => handleSort('description')}>
                Описание {getSortIcon('description')}
              </Dropdown.Item>
              <Dropdown.Item onClick={() => handleSort('amount')}>
                Сумма {getSortIcon('amount')}
              </Dropdown.Item>
              <Dropdown.Item onClick={() => handleSort('type')}>
                Тип {getSortIcon('type')}
              </Dropdown.Item>
            </Dropdown.Menu>
          </Dropdown>
        </div>
      </div>

      <div className="mb-3">
        <small className="text-muted">
          Текущая сортировка: 
          <strong>
            {sortConfig.key === 'date' ? ' Дата' : 
             sortConfig.key === 'category' ? ' Категория' :
             sortConfig.key === 'amount' ? ' Сумма' :
             sortConfig.key === 'type' ? ' Тип' : ' Описание'}
            {sortConfig.direction === 'asc' ? ' по возрастанию' : ' по убыванию'}
          </strong>
          . Кликните на заголовок столбца для изменения сортировки.
        </small>
      </div>

      {error && <Alert variant="danger" onClose={() => setError('')} dismissible>{error}</Alert>}

      {sortedTransactions.length === 0 ? (
        <Alert variant="info">
          У вас пока нет транзакций. Добавьте первую!
        </Alert>
      ) : (
        <Table striped bordered hover responsive>
          <thead>
            <tr>
              <th 
                style={{ cursor: 'pointer', userSelect: 'none' }}
                onClick={() => handleSort('date')}
                className="position-relative"
              >
                <div className="d-flex justify-content-between align-items-center">
                  <span>Дата</span>
                  <span className="ms-2">
                    {sortConfig.key === 'date' ? 
                      (sortConfig.direction === 'asc' ? '⬆️' : '⬇️') : 
                      '↕️'}
                  </span>
                </div>
              </th>
              <th 
                style={{ cursor: 'pointer', userSelect: 'none' }}
                onClick={() => handleSort('category')}
                className="position-relative"
              >
                <div className="d-flex justify-content-between align-items-center">
                  <span>Категория</span>
                  <span className="ms-2">
                    {sortConfig.key === 'category' ? 
                      (sortConfig.direction === 'asc' ? '⬆️' : '⬇️') : 
                      '↕️'}
                  </span>
                </div>
              </th>
              <th 
                style={{ cursor: 'pointer', userSelect: 'none' }}
                onClick={() => handleSort('description')}
                className="position-relative"
              >
                <div className="d-flex justify-content-between align-items-center">
                  <span>Описание</span>
                  <span className="ms-2">
                    {sortConfig.key === 'description' ? 
                      (sortConfig.direction === 'asc' ? '⬆️' : '⬇️') : 
                      '↕️'}
                  </span>
                </div>
              </th>
              <th 
                style={{ cursor: 'pointer', userSelect: 'none' }}
                onClick={() => handleSort('amount')}
                className="position-relative"
              >
                <div className="d-flex justify-content-between align-items-center">
                  <span>Сумма</span>
                  <span className="ms-2">
                    {sortConfig.key === 'amount' ? 
                      (sortConfig.direction === 'asc' ? '⬆️' : '⬇️') : 
                      '↕️'}
                  </span>
                </div>
              </th>
              <th 
                style={{ cursor: 'pointer', userSelect: 'none' }}
                onClick={() => handleSort('type')}
                className="position-relative"
              >
                <div className="d-flex justify-content-between align-items-center">
                  <span>Тип</span>
                  <span className="ms-2">
                    {sortConfig.key === 'type' ? 
                      (sortConfig.direction === 'asc' ? '⬆️' : '⬇️') : 
                      '↕️'}
                  </span>
                </div>
              </th>
              <th>Действия</th>
            </tr>
          </thead>
          <tbody>
            {sortedTransactions.map(t => (
              <tr key={t.id}>
                <td>{formatDate(t.date)}</td>
                <td>
                  <Badge 
                    style={{ 
                      backgroundColor: t.categoryColor || '#808080',
                      color: '#fff'
                    }}
                  >
                    {t.categoryIcon || '💰'} {t.category}
                  </Badge>
                </td>
                <td>{t.description || '-'}</td>
                <td className={t.isIncome ? 'text-success' : 'text-danger'}>
                  {t.amount.toFixed(2)} ₽
                </td>
                <td>
                  {t.isIncome ? 
                    <Badge bg="success">Доход</Badge> : 
                    <Badge bg="secondary">Расход</Badge>
                  }
                </td>
                <td>
                  <Button 
                    variant="outline-primary" 
                    size="sm" 
                    className="me-2"
                    onClick={() => handleEdit(t)}
                  >
                    Изменить
                  </Button>
                  <Button 
                    variant="outline-danger" 
                    size="sm"
                    onClick={() => handleDelete(t.id)}
                  >
                    Удалить
                  </Button>
                </td>
              </tr>
            ))}
          </tbody>
        </Table>
      )}

      {/* Статистика по отфильтрованным транзакциям */}
      {sortedTransactions.length > 0 && (
        <div className="mt-3 p-3 bg-light rounded">
          <h5>Статистика по текущему виду:</h5>
          <div className="row">
            <div className="col-md-3">
              <strong>Всего транзакций:</strong> {sortedTransactions.length}
            </div>
            <div className="col-md-3">
              <strong>Доходы:</strong> 
              <span className="text-success">
                {' '}{sortedTransactions.filter(t => t.isIncome).reduce((sum, t) => sum + t.amount, 0).toFixed(2)} ₽
              </span>
            </div>
            <div className="col-md-3">
              <strong>Расходы:</strong> 
              <span className="text-danger">
                {' '}{sortedTransactions.filter(t => !t.isIncome).reduce((sum, t) => sum + t.amount, 0).toFixed(2)} ₽
              </span>
            </div>
            <div className="col-md-3">
              <strong>Баланс:</strong> 
              <span className={sortedTransactions.filter(t => t.isIncome).reduce((sum, t) => sum + t.amount, 0) >= 
                              sortedTransactions.filter(t => !t.isIncome).reduce((sum, t) => sum + t.amount, 0) ? 
                              'text-success' : 'text-danger'}>
                {' '}{sortedTransactions.reduce((sum, t) => t.isIncome ? sum + t.amount : sum - t.amount, 0).toFixed(2)} ₽
              </span>
            </div>
          </div>
        </div>
      )}

      {/* Модальное окно для добавления/редактирования транзакции */}
      <Modal show={showModal} onHide={() => {
        setShowModal(false);
        setEditingTransaction(null);
        setFormData({ 
          amount: '', 
          category: '', 
          description: '', 
          isIncome: false,
          categoryColor: '#808080',
          categoryIcon: '💰'
        });
      }}>
        <Modal.Header closeButton>
          <Modal.Title>
            {editingTransaction ? 'Редактировать транзакцию' : 'Новая транзакция'}
          </Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <Form>
            <Form.Group className="mb-3">
              <Form.Label>Тип *</Form.Label>
              <div>
                <Button
                  variant={formData.isIncome ? 'success' : 'outline-success'}
                  className="me-2"
                  onClick={() => {
                    setFormData({
                      ...formData, 
                      isIncome: true,
                      category: '' // Сбрасываем категорию при смене типа
                    });
                  }}
                >
                  Доход
                </Button>
                <Button
                  variant={!formData.isIncome ? 'danger' : 'outline-danger'}
                  onClick={() => {
                    setFormData({
                      ...formData, 
                      isIncome: false,
                      category: '' // Сбрасываем категорию при смене типа
                    });
                  }}
                >
                  Расход
                </Button>
              </div>
            </Form.Group>

            <Form.Group className="mb-3">
              <Form.Label>Сумма *</Form.Label>
              <InputGroup>
                <InputGroup.Text>₽</InputGroup.Text>
                <FormControl
                  type="number"
                  step="0.01"
                  min="0.01"
                  placeholder="0.00"
                  value={formData.amount}
                  onChange={e => setFormData({...formData, amount: e.target.value})}
                  required
                />
              </InputGroup>
            </Form.Group>

            <Form.Group className="mb-3">
              <Form.Label>Категория *</Form.Label>
              <Form.Select
                value={formData.category}
                onChange={e => handleCategoryChange(e.target.value)}
                required
              >
                <option value="">Выберите категорию</option>
                {availableCategories.map(cat => (
                  <option key={cat.id} value={cat.name}>
                    {cat.icon} {cat.name}
                  </option>
                ))}
              </Form.Select>
              <Form.Text className="text-muted">
                {availableCategories.length === 0 && 
                  `Для ${formData.isIncome ? 'доходов' : 'расходов'} нет категорий. Создайте их в админ-панели.`
                }
              </Form.Text>
            </Form.Group>

            <Form.Group className="mb-3">
              <Form.Label>Описание</Form.Label>
              <Form.Control
                as="textarea"
                rows={3}
                placeholder="Дополнительная информация..."
                value={formData.description}
                onChange={e => setFormData({...formData, description: e.target.value})}
              />
            </Form.Group>
          </Form>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={() => setShowModal(false)}>
            Отмена
          </Button>
          <Button variant="primary" onClick={handleSubmit} disabled={availableCategories.length === 0}>
            {editingTransaction ? 'Сохранить' : 'Добавить'}
          </Button>
        </Modal.Footer>
      </Modal>
    </div>
  );
}
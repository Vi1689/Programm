import React, { createContext, useState, useContext, useEffect } from 'react';

const AuthContext = createContext(null);

export const useAuth = () => {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error('useAuth must be used within AuthProvider');
  }
  return context;
};

export const AuthProvider = ({ children }) => {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    // Проверка сохраненного токена при загрузке
    const token = localStorage.getItem('budget_token');
    const userData = localStorage.getItem('budget_user');
    
    if (token && userData) {
      setUser(JSON.parse(userData));
    }
    setLoading(false);
  }, []);

  const login = (token, userData) => {
    localStorage.setItem('budget_token', token);
    localStorage.setItem('budget_user', JSON.stringify(userData));
    setUser(userData);
  };

  const logout = () => {
    localStorage.removeItem('budget_token');
    localStorage.removeItem('budget_user');
    setUser(null);
  };

  const isAdmin = () => user?.role === 'Admin';

  const getToken = () => localStorage.getItem('budget_token');

  return (
    <AuthContext.Provider value={{ 
      user, 
      loading, 
      login, 
      logout, 
      isAdmin, 
      getToken 
    }}>
      {children}
    </AuthContext.Provider>
  );
};
import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import { AuthProvider } from './context/AuthContext';
import NavbarComponent from './components/Navbar';
import ProtectedRoute from './components/ProtectedRoute';
import Login from './pages/Login';
import Register from './pages/Register';
import ValeraList from './pages/ValeraList';
import AdminValeraList from './pages/AdminValeraList';
import ValeraStats from './pages/ValeraStats';
import 'bootstrap/dist/css/bootstrap.min.css';

export default function App() {
  return (
    <Router>
      <AuthProvider>
        <NavbarComponent />
        <Routes>
          {/* Публичные маршруты */}
          <Route path="/" element={<Navigate to="/login" />} />
          <Route path="/login" element={<Login />} />
          <Route path="/register" element={<Register />} />
          
          {/* Защищенные маршруты для всех авторизованных */}
          <Route 
            path="/valera" 
            element={
              <ProtectedRoute>
                <ValeraList />
              </ProtectedRoute>
            } 
          />
          
          <Route 
            path="/valera/:id" 
            element={
              <ProtectedRoute>
                <ValeraStats />
              </ProtectedRoute>
            } 
          />
          
          {/* Защищенные маршруты только для админов */}
          <Route 
            path="/admin/valera" 
            element={
              <ProtectedRoute adminOnly={true}>
                <AdminValeraList />
              </ProtectedRoute>
            } 
          />

          {/* 404 - редирект на login */}
          <Route path="*" element={<Navigate to="/login" />} />
        </Routes>
      </AuthProvider>
    </Router>
  );
}
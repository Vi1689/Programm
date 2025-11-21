import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import ValeraList from './components/ValeraList';
import ValeraStats from './components/ValeraStats';

export default function App() {
  return (
    <Router>
      <Routes>
        {}
        <Route path="/" element={<ValeraList />} />

        {}
        <Route path="/valera/:id" element={<ValeraStats />} />

        {}
        <Route path="*" element={<Navigate to="/" />} />
      </Routes>
    </Router>
  );
}

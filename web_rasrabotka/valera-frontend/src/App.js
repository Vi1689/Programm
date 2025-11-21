import { BrowserRouter, Routes, Route } from "react-router-dom";
import ValeraList from "./components/ValeraList";
import ValeraStats from "./components/ValeraStats";

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<ValeraList />} />
        <Route path="/valera/:id" element={<ValeraStats />} />
      </Routes>
    </BrowserRouter>
  );
}

export default App;

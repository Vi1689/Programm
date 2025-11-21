import { useEffect, useState } from "react";
import { getAllValeras, createValera } from "../api/valeraApi";
import { useNavigate } from "react-router-dom";

export default function ValeraList() {
    const [valeras, setValeras] = useState([]);
    const [search, setSearch] = useState("");
    const [form, setForm] = useState({ name: "", health: 100, mana: 0, cheerfulness: 0, fatigue: 0, money: 0 });

    const navigate = useNavigate();

    async function load() {
        setValeras(await getAllValeras());
    }

    useEffect(() => { load(); }, []);

    function filtered() {
        return valeras.filter(v => v.name?.toLowerCase().includes(search.toLowerCase()));
    }

    async function create() {
        await createValera(form);
        load();
    }

    return (
        <div style={{ padding: 20 }}>
            <h1>Список Валер</h1>

            <input
                placeholder="Поиск по имени"
                value={search}
                onChange={e => setSearch(e.target.value)}
            />

            <h2>Создать Валеру</h2>
            <input placeholder="Имя"
                onChange={e => setForm({ ...form, name: e.target.value })}
            />
            <button onClick={create}>Создать</button>

            <h2>Все Валеры</h2>

            {filtered().map(v => (
                <div key={v.id}
                    style={{ cursor: "pointer", padding: 10, border: "1px solid gray", marginTop: 10 }}
                    onClick={() => navigate(`/valera/${v.id}`)}>
                    {v.name} — здоровье: {v.health}, усталость: {v.fatigue}
                </div>
            ))}
        </div>
    );
}

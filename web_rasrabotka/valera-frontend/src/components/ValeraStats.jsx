import { useEffect, useState } from "react";
import { getValera, action } from "../api/valeraApi";
import { useParams } from "react-router-dom";

export default function ValeraStats() {
    const { id } = useParams();
    const [v, setV] = useState(null);

    async function load() {
        setV(await getValera(id));
    }

    async function doAction(act) {
        await action(id, act);
        load();
    }

    useEffect(() => { load(); }, []);

    if (!v) return <div>Загрузка...</div>;

    return (
        <div style={{ padding: 20 }}>
            <h1>Валера: {v.name}</h1>

            <p>Здоровье: {v.health}</p>
            <progress value={v.health} max="100" />

            <p>Алкоголь: {v.mana}</p>
            <progress value={v.mana} max="100" />

            <p>Жизнерадостность: {v.cheerfulness}</p>
            <progress value={v.cheerfulness + 10} max="20" />

            <p>Усталость: {v.fatigue}</p>
            <progress value={v.fatigue} max="100" />

            <p>Деньги: {v.money}</p>

            <h2>Действия</h2>

            <button
                disabled={v.mana >= 50 || v.fatigue >= 10}
                onClick={() => doAction("work")}
            >
                Пойти на работу
            </button>

            <button onClick={() => doAction("nature")}>Созерцать природу</button>
            <button onClick={() => doAction("wine")}>Пить вино и смотреть сериал</button>
            <button onClick={() => doAction("bar")}>Сходить в бар</button>
            <button onClick={() => doAction("marginals")}>Выпить с маргиналами</button>
            <button onClick={() => doAction("metro")}>Петь в метро</button>
            <button onClick={() => doAction("sleep")}>Спать</button>
        </div>
    );
}

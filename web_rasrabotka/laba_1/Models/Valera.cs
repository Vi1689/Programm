namespace ValeraAPI.Models
{
    public class Valera
    {
        public int Id { get; set; }
        public string Name { get; set; } = "Valera";

        public int Health { get; private set; } = 100;
        public int Mana { get; private set; }
        public int Cheerfulness { get; private set; }
        public int Fatigue { get; private set; }
        public int Money { get; private set; }

        public Valera() { }

        public Valera(string name = "Valera", int health = 100, int mana = 0, int cheerfulness = 0, int fatigue = 0, int money = 0)
        {
            Name = name;
            Health = Check(health, 0, 100);
            Mana = Check(mana, 0, 100);
            Cheerfulness = Check(cheerfulness, -10, 10);
            Fatigue = Check(fatigue, 0, 100);
            Money = money;
        }

        private int Check(int value, int min, int max) => value < min ? min : value > max ? max : value;

        public bool GoWork()
        {
            if (Mana >= 50 || Fatigue >= 10) return false;

            Cheerfulness = Check(Cheerfulness - 5, -10, 10);
            Mana = Check(Mana - 30, 0, 100);
            Money += 100;
            Fatigue = Check(Fatigue + 70, 0, 100);

            return true;
        }

        public void ContemplateNature()
        {
            Cheerfulness = Check(Cheerfulness + 1, -10, 10);
            Mana = Check(Mana - 10, 0, 100);
            Fatigue = Check(Fatigue + 10, 0, 100);
        }

        public void DrinkWineAndWatchSeries()
        {
            Cheerfulness = Check(Cheerfulness - 1, -10, 10);
            Mana = Check(Mana + 30, 0, 100);
            Fatigue = Check(Fatigue + 10, 0, 100);
            Health = Check(Health - 5, 0, 100);
            Money -= 20;
        }

        public void GoBar()
        {
            Cheerfulness = Check(Cheerfulness + 1, -10, 10);
            Mana = Check(Mana + 60, 0, 100);
            Fatigue = Check(Fatigue + 40, 0, 100);
            Health = Check(Health - 10, 0, 100);
            Money -= 100;
        }

        public void DrinkWithMarginals()
        {
            Cheerfulness = Check(Cheerfulness + 5, -10, 10);
            Health = Check(Health - 80, 0, 100);
            Mana = Check(Mana + 90, 0, 100);
            Fatigue = Check(Fatigue + 80, 0, 100);
            Money -= 150;
        }

        public void SingInMetro()
        {
            Money += 10 + ((Mana > 40 && Mana < 70) ? 50 : 0);
            Cheerfulness = Check(Cheerfulness + 1, -10, 10);
            Mana = Check(Mana + 10, 0, 100);
            Fatigue = Check(Fatigue + 20, 0, 100);
        }

        public void Sleep()
        {
            if (Mana < 30)
                Health = Check(Health + 90, 0, 100);

            if (Mana > 70)
                Cheerfulness = Check(Cheerfulness - 3, -10, 10);

            Mana = Check(Mana - 50, 0, 100);
            Fatigue = Check(Fatigue - 70, 0, 100);
        }
    }
}

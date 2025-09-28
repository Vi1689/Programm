using Xunit;
using ValeraAPI.Models;

namespace ValeraAPI.Tests
{
    public class ValeraTests
    {
        [Fact]
        public void TEST1()
        {
            var valera = new Valera();

            bool result = valera.GoWork();

            Assert.True(result);
            Assert.Equal(0, valera.Mana);
            Assert.Equal(70, valera.Fatigue);
            Assert.Equal(-5, valera.Cheerfulness);
            Assert.Equal(100, valera.Money);
        }
        [Fact]
        public void TEST2()
        {
            var valera = new Valera(mana: 50);

            bool result = valera.GoWork();

            Assert.False(result);
        }
        [Fact]
        public void TEST3()
        {
            var valera = new Valera(fatigue: 10);

            bool result = valera.GoWork();

            Assert.False(result);
        }

        [Fact]
        public void TEST4()
        {
            var valera = new Valera();

            valera.ContemplateNature();

            Assert.Equal(0, valera.Mana);
            Assert.Equal(10, valera.Fatigue);
            Assert.Equal(1, valera.Cheerfulness);
        }
        [Fact]
        public void TEST5()
        {
            var valera = new Valera(mana: 100);

            valera.ContemplateNature();

            Assert.Equal(90, valera.Mana);
            Assert.Equal(10, valera.Fatigue);
            Assert.Equal(1, valera.Cheerfulness);
        }
        [Fact]
        public void TEST6()
        {
            var valera = new Valera(fatigue: 100);

            valera.ContemplateNature();

            Assert.Equal(0, valera.Mana);
            Assert.Equal(100, valera.Fatigue);
            Assert.Equal(1, valera.Cheerfulness);
        }

        [Fact]
        public void TEST7()
        {
            var valera = new Valera();

            valera.DrinkWineAndWatchSeries();

            Assert.Equal(30, valera.Mana);
            Assert.Equal(10, valera.Fatigue);
            Assert.Equal(-1, valera.Cheerfulness);
            Assert.Equal(-20, valera.Money);
            Assert.Equal(95, valera.Health);
        }
        [Fact]
        public void TEST8()
        {
            var valera = new Valera();

            valera.GoBar();

            Assert.Equal(60, valera.Mana);
            Assert.Equal(40, valera.Fatigue);
            Assert.Equal(1, valera.Cheerfulness);
            Assert.Equal(-100, valera.Money);
            Assert.Equal(90, valera.Health);
        }
        [Fact]
        public void TEST9()
        {
            var valera = new Valera();

            valera.DrinkWithMarginals();

            Assert.Equal(90, valera.Mana);
            Assert.Equal(80, valera.Fatigue);
            Assert.Equal(5, valera.Cheerfulness);
            Assert.Equal(20, valera.Health);
            Assert.Equal(-150, valera.Money);
        }

        [Fact]
        public void TEST10()
        {
            var valera = new Valera();

            valera.SingInMetro();

            Assert.Equal(10, valera.Money);
            Assert.Equal(1, valera.Cheerfulness);
            Assert.Equal(10, valera.Mana);
            Assert.Equal(20, valera.Fatigue);
        }
        [Fact]
        public void TEST11()
        {
            var valera = new Valera(mana: 60);

            valera.SingInMetro();

            Assert.Equal(60, valera.Money);
            Assert.Equal(1, valera.Cheerfulness);
            Assert.Equal(70, valera.Mana);
            Assert.Equal(20, valera.Fatigue);
        }
        [Fact]
        public void TEST12()
        {
            var valera = new Valera(mana: 100);

            valera.SingInMetro();

            Assert.Equal(10, valera.Money);
            Assert.Equal(1, valera.Cheerfulness);
            Assert.Equal(100, valera.Mana);
            Assert.Equal(20, valera.Fatigue);
        }
        [Fact]
        public void TEST13()
        {
            var valera = new Valera();

            valera.Sleep();

            Assert.Equal(100, valera.Health);
            Assert.Equal(0, valera.Cheerfulness);
            Assert.Equal(0, valera.Mana);
            Assert.Equal(0, valera.Fatigue);
        }
        [Fact]
        public void TEST14()
        {
            var valera = new Valera(mana: 100, health: 10);

            valera.Sleep();

            Assert.Equal(10, valera.Health);
            Assert.Equal(-3, valera.Cheerfulness);
            Assert.Equal(50, valera.Mana);
            Assert.Equal(0, valera.Fatigue);
        }
    }
}

using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace laba_1.Migrations
{
    /// <inheritdoc />
    public partial class AddNameToValera : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "Name",
                table: "Valeras",
                type: "TEXT",
                nullable: false,
                defaultValue: "");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Name",
                table: "Valeras");
        }
    }
}

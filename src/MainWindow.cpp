#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    run_example();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_example()
{
    SpaceController space_controller;

    space_controller.createBoundary("Outer Wall");
    space_controller.addBoundaryPoint(0, 0, 0);
    space_controller.addBoundaryPoint(0, 400, 0);
    space_controller.addBoundaryPoint(0, 400, 200);
    space_controller.addBoundaryPoint(0, 160, 200);
    space_controller.addBoundaryPoint(0, 160, 400);
    space_controller.addBoundaryPoint(0, 400, 400);
    space_controller.addBoundaryPoint(0, 400, 800);
    space_controller.addBoundaryPoint(0, 0, 800);

    space_controller.createRoom("Meeting Room");
    space_controller.createRoom("Gaming Room");
    space_controller.createRoom("Manager Department");
    space_controller.createRoom("Manager Department");
    space_controller.createRoom("Gaming Room");
    space_controller.createRoom("Meeting Room");

    space_controller.addRoomOnBoundary(0, 0);
    space_controller.addRoomOnBoundary(1, 0);
    space_controller.addRoomOnBoundary(2, 0);
    space_controller.addRoomOnBoundary(3, 0);
    space_controller.addRoomOnBoundary(4, 0);
    space_controller.addRoomOnBoundary(5, 0);

    space_controller.setRoomNeighboor(0, 1);
    space_controller.setRoomNeighboor(1, 2);
    // space_controller.setRoomNeighboor(0, 2);

    space_controller.setRoomNeighboor(3, 4);
    space_controller.setRoomNeighboor(4, 5);

    std::vector<EasyRoomLine> room_line_vec;

    space_controller.getSortedRoomLineVec(room_line_vec);

    for(const EasyRoomLine &room_line : room_line_vec)
    {
        std::cout << "Line : " << std::endl;

        for(const size_t room_idx : room_line.sorted_room_idx_line)
        {
            std::cout << room_idx << " - ";
        }

        std::cout << std::endl;
    }

    space_controller.showBoundary();
}

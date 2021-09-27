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
    size_t demo_mode = 2;

    SpaceController space_controller;

    space_controller.createBoundary("Outer Wall");
    space_controller.setOuterBoundary(0);

    switch(demo_mode)
    {
        case 0:
            space_controller.addBoundaryPoint(0, 0, 0);
            space_controller.addBoundaryPoint(0, 400, 0);
            space_controller.addBoundaryPoint(0, 400, 200);
            space_controller.addBoundaryPoint(0, 160, 200);
            space_controller.addBoundaryPoint(0, 160, 400);
            space_controller.addBoundaryPoint(0, 400, 400);
            space_controller.addBoundaryPoint(0, 400, 800);
            space_controller.addBoundaryPoint(0, 0, 800);

            space_controller.updateBoundary();

            space_controller.createRoom("Meeting Room");
            space_controller.setRoomSize(0, 100, 100);
            space_controller.createRoom("Gaming Room");
            space_controller.setRoomSize(1, 100, 100);
            space_controller.createRoom("Manager Department");
            space_controller.setRoomSize(2, 100, 100);
            space_controller.createRoom("Manager Department");
            space_controller.setRoomSize(3, 100, 100);
            space_controller.createRoom("Gaming Room");
            space_controller.setRoomSize(4, 100, 100);
            space_controller.createRoom("Meeting Room");
            space_controller.setRoomSize(5, 100, 100);

            space_controller.setRoomNeighboor(0, 1);
            space_controller.setRoomNeighboor(1, 2);
            space_controller.setRoomNeighboor(0, 2);

            space_controller.setRoomNeighboor(3, 4);
            space_controller.setRoomNeighboor(4, 5);

            space_controller.updateRoomConnection();

            space_controller.setRoomBoundaryPointParam(0, 0, 0, 0);
            space_controller.setRoomBoundaryPointParam(4, 0, 6, 0);

            space_controller.updateRoom();

            space_controller.showSpace(0);

            break;
        case 1:
            space_controller.addBoundaryPoint(0, 0, 0);
            space_controller.addBoundaryPoint(0, 400, 0);
            space_controller.addBoundaryPoint(0, 400, 400);
            space_controller.addBoundaryPoint(0, 0, 400);

            space_controller.updateBoundary();

            space_controller.createRoom("MR 1");
            space_controller.setRoomSize(0, 100, 70);
            space_controller.createRoom("MR 2");
            space_controller.setRoomSize(1, 100, 70);
            space_controller.createRoom("MR 3");
            space_controller.setRoomSize(2, 100, 80);

            space_controller.setRoomNeighboor(0, 1);
            space_controller.setRoomNeighboor(1, 2);

            space_controller.createRoom("MR 4");
            space_controller.setRoomSize(3, 100, 100);
            space_controller.createRoom("MR 5");
            space_controller.setRoomSize(4, 100, 100);

            space_controller.updateRoomConnection();

            space_controller.setRoomBoundaryPointParam(2, 0, 0, 1);
            space_controller.setRoomBoundaryPointParam(3, 0, 2, 0);
            space_controller.setRoomBoundaryPointParam(4, 0, 2, 1);

            space_controller.updateRoom();

            space_controller.showSpace(0);

            break;
        case 2:
            space_controller.addBoundaryPoint(0, 0, 0);
            space_controller.addBoundaryPoint(0, 400, 0);
            space_controller.addBoundaryPoint(0, 400, 400);
            space_controller.addBoundaryPoint(0, 0, 400);

            space_controller.updateBoundary();

            space_controller.createRoom("MR 1");
            space_controller.setRoomSize(0, 100, 70);
            space_controller.createRoom("MR 2");
            space_controller.setRoomSize(1, 100, 70);
            space_controller.createRoom("MR 3");
            space_controller.setRoomSize(2, 100, 80);

            space_controller.setRoomNeighboor(0, 1);
            space_controller.setRoomNeighboor(1, 2);

            space_controller.createRoom("MR 4");
            space_controller.setRoomSize(3, 100, 100);
            space_controller.createRoom("MR 5");
            space_controller.setRoomSize(4, 100, 100);

            space_controller.updateRoomConnection();

            while(true)
            {
                size_t random_room_2_boundary_line_idx = std::rand() % 4;
                size_t random_room_3_boundary_line_idx = std::rand() % 4;
                size_t random_room_4_boundary_line_idx = std::rand() % 4;
                space_controller.setRoomBoundaryPointParam(2, 0, random_room_2_boundary_line_idx, 1);
                space_controller.setRoomBoundaryPointParam(3, 0, random_room_3_boundary_line_idx, 0);
                space_controller.setRoomBoundaryPointParam(4, 0, random_room_4_boundary_line_idx, 1);

                space_controller.updateRoom();

                space_controller.showSpace(1);
            }

            break;
    }
}


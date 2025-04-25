package homework.ch11_13.p4;

public class ComponentFactory {

    ComponentFactory() {

    }

    public static Component create(){
        int id = 0;

        Component computor = new CompositeComponent(id++, "Think Pad", 0.0);

        Component keyboard = new AtomicComponent(id++, "Keyboard",20.0);
        Component mouse = new AtomicComponent(id++, "Mouse", 20.0);
        Component monitor = new AtomicComponent(id++, "Monitor", 1000.0);
        computor.add(keyboard);
        computor.add(mouse);
        computor.add(monitor);


        Component mainFrame = new CompositeComponent(id++, "Main frame", 0.0);

        Component hardDisk = new AtomicComponent(id++, "Hard dist", 1000);
        Component powerSupplier = new AtomicComponent(id++, "Power supplier", 500);
        mainFrame.add(hardDisk);
        mainFrame.add(powerSupplier);

        Component mainBoard = new CompositeComponent(id++, "Main board", 0.0);
        Component cpu = new AtomicComponent(id++, "CPU", 1500.0);
        Component videoCard = new AtomicComponent(id++, "Video card", 900);
        Component networkCard = new AtomicComponent(id++, "Netword card", 100);
        mainBoard.add(cpu);
        mainBoard.add(videoCard);
        mainBoard.add(networkCard);

        computor.add(mainFrame);
        mainFrame.add(mainBoard);

        return computor;
    }
}

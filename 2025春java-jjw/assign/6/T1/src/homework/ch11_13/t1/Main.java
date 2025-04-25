package homework.ch11_13.t1;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {

        Task task1 = new Eat();
        Task task2 = new Play();
        Task task3 = new Sleep();
//        task1.execute();
//        task2.execute();
//        task3.execute();

        TaskService taskService = new TaskServiceImpl();
        taskService.addTask(task1);
        taskService.addTask(task2);
        taskService.addTask(task3);

        taskService.exeuteTasks();
    }
}

class Eat implements Task {

    @Override
    public void execute() {
        System.out.println("I'm going to eat something at dong 1.");
    }
}

class Sleep implements Task {

    @Override
    public void execute() {
        System.out.println("I'm going to sleep with air conditioner.");
    }
}

class Play implements Task {

    @Override
    public void execute() {
        System.out.println("I'm going to play a little 1v1 with donk.");
    }
}


class TaskServiceImpl implements TaskService{

    private ArrayList<Task> taskArrayList = new ArrayList<Task>();;

    @Override
    public void exeuteTasks() {
        for (Task task: taskArrayList){
            task.execute();
        }
    }

    @Override
    public void addTask(Task t) {
        taskArrayList.add(t);
    }
}

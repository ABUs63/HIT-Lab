import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class Monkey_Banana {
    //初始化三个物体
    private static Monkey monkey = new Monkey();
    private static Box box = new Box();
    private static Banana banana = new Banana();

    private static void init(int x, int y) {//x和y为区域的范围
        int mx, my, bx, by, bax, bay;//三个物体的初始坐标
        Random random = new Random();
        mx = random.nextInt(x) + 1;//生成1~x范围内的横坐标
        do {
            bx = random.nextInt(x) + 1;
        } while (mx == bx);//横坐标不同
        do {
            bax = random.nextInt(x) + 1;
        } while (mx == bax || bax == bx);
        my = random.nextInt(y) + 1;//生成1~x范围内的纵坐标
        do {
            by = random.nextInt(y) + 1;
        } while (my == by);//纵坐标不同
        do {
            bay = random.nextInt(y) + 1;
        } while (my == bay || bay == by);
        //设置三个物体的位置
        monkey.setLocation(mx, my);//初始位置a
        box.setLocation(bx, by);//初始位置b
        banana.setLocation(bax, bay);//初始位置c

        monkey.setHold(false);//初始没有握着香蕉
        monkey.setNeedbox(false);//初始不需要箱子，当够不到香蕉则需要
        monkey.setOn(false);//初始不在箱子上

        banana.setHang(true);//是否处于悬挂状态
    }

    private static boolean canfinish() {//查询是否到目标状态
        return monkey.isHold() && monkey.getLocation().equals(box.getLocation())
                && monkey.getLocation().equals(banana.getLocation()) && !banana.isHang()
                && monkey.isOn();
    }

    private static String getState() {//获取当前三个物体位置
        String result = "";
        result += "猴子的当前位置为" + monkey.getLocation().toString() + "\n";
        result += "箱子的当前位置为" + box.getLocation().toString() + "\n";
        result += "香蕉的当前位置为" + banana.getLocation().toString();
        return result;
    }

    //产生式的条件以if分支条件进行模拟，动作以if体进行模拟
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int roomx, roomy;
        do{
            System.out.println("请输入区域宽度x");
            roomx = scanner.nextInt();
            System.out.println("请输入区域长度y");
            roomy = scanner.nextInt();
        }while(roomx*roomy<3&&(roomx<0||roomy<0));
        System.out.println("即将生成宽度:" + roomx + "长度:" + roomy + "区域");
        init(roomx, roomy);
        System.out.println("猴子的初始位置为" + monkey.getLocation().toString());
        System.out.println("箱子的初始位置为" + box.getLocation().toString());
        System.out.println("香蕉的初始位置为" + banana.getLocation().toString());
        System.out.println("猴子即将行动！");
        System.out.println("--------------------------------------------------");
        try {
            TimeUnit.SECONDS.sleep(2);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        while (!canfinish()) {
            System.out.println("--------------------------------------------------");
            if (!monkey.isNeedbox()&&!monkey.getLocation().equals(banana.getLocation())) {//猴子没有发现够不到香蕉，直接Goto香蕉位置
                monkey.setLocation(banana.getLocation().getX(), banana.getLocation().getY());
                System.out.println("Monkey Goto the location of banana");
                System.out.println(getState());
                try {
                    TimeUnit.SECONDS.sleep(2);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                continue;
            }
            if (!monkey.isNeedbox() && monkey.getLocation().equals(banana.getLocation())) {
                //猴子发现够不到香蕉，需要箱子
                monkey.setNeedbox(true);
                System.out.println("Monkey cannot grasp banana,it needs box");
                System.out.println(getState());
                try {
                    TimeUnit.SECONDS.sleep(2);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                continue;
            }
            if (monkey.isNeedbox() && !monkey.getLocation().equals(box.getLocation())) {
                //需要箱子的时候Goto箱子位置
                monkey.setLocation(box.getLocation().getX(), box.getLocation().getY());
                System.out.println("Monkey Goto the location of box");
                System.out.println(getState());
                try {
                    TimeUnit.SECONDS.sleep(2);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                continue;
            }
            if (monkey.isNeedbox() && monkey.getLocation().equals(box.getLocation())&&!monkey.getLocation().equals(banana.getLocation())) {
                //推箱子Pushbox
                monkey.setLocation(banana.getLocation().getX(), banana.getLocation().getY());
                box.setLocation(banana.getLocation().getX(), banana.getLocation().getY());
                System.out.println("Monkey Pushbox to the location of banana");
                System.out.println(getState());
                try {
                    TimeUnit.SECONDS.sleep(2);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                continue;
            }
            if (monkey.isNeedbox() && monkey.getLocation().equals(box.getLocation()) && monkey.getLocation().equals(banana.getLocation())&&!monkey.isOn()) {
                //箱子在香蕉下，猴子需要爬上箱子Climbbox
                monkey.setOn(true);
                System.out.println("Monkey Climbbox,now it can grasp banana");
                System.out.println(getState());
                try {
                    TimeUnit.SECONDS.sleep(2);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                continue;
            }
            if (monkey.isNeedbox() && monkey.getLocation().equals(box.getLocation()) && monkey.getLocation().equals(banana.getLocation()) && monkey.isOn()) {
                //猴子在箱子上，箱子在香蕉下，需要抓香蕉Grasp
                monkey.setHold(true);
                banana.setHang(false);
                System.out.println("Monkey grasps banana");
                System.out.println(getState());
                try {
                    TimeUnit.SECONDS.sleep(2);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
        System.out.println("猴子获得了香蕉");
    }
}

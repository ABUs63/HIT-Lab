import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class Monkey_Banana {
    //��ʼ����������
    private static Monkey monkey = new Monkey();
    private static Box box = new Box();
    private static Banana banana = new Banana();

    private static void init(int x, int y) {//x��yΪ����ķ�Χ
        int mx, my, bx, by, bax, bay;//��������ĳ�ʼ����
        Random random = new Random();
        mx = random.nextInt(x) + 1;//����1~x��Χ�ڵĺ�����
        do {
            bx = random.nextInt(x) + 1;
        } while (mx == bx);//�����겻ͬ
        do {
            bax = random.nextInt(x) + 1;
        } while (mx == bax || bax == bx);
        my = random.nextInt(y) + 1;//����1~x��Χ�ڵ�������
        do {
            by = random.nextInt(y) + 1;
        } while (my == by);//�����겻ͬ
        do {
            bay = random.nextInt(y) + 1;
        } while (my == bay || bay == by);
        //�������������λ��
        monkey.setLocation(mx, my);//��ʼλ��a
        box.setLocation(bx, by);//��ʼλ��b
        banana.setLocation(bax, bay);//��ʼλ��c

        monkey.setHold(false);//��ʼû�������㽶
        monkey.setNeedbox(false);//��ʼ����Ҫ���ӣ����������㽶����Ҫ
        monkey.setOn(false);//��ʼ����������

        banana.setHang(true);//�Ƿ�������״̬
    }

    private static boolean canfinish() {//��ѯ�Ƿ�Ŀ��״̬
        return monkey.isHold() && monkey.getLocation().equals(box.getLocation())
                && monkey.getLocation().equals(banana.getLocation()) && !banana.isHang()
                && monkey.isOn();
    }

    private static String getState() {//��ȡ��ǰ��������λ��
        String result = "";
        result += "���ӵĵ�ǰλ��Ϊ" + monkey.getLocation().toString() + "\n";
        result += "���ӵĵ�ǰλ��Ϊ" + box.getLocation().toString() + "\n";
        result += "�㽶�ĵ�ǰλ��Ϊ" + banana.getLocation().toString();
        return result;
    }

    //����ʽ��������if��֧��������ģ�⣬������if�����ģ��
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int roomx, roomy;
        do{
            System.out.println("������������x");
            roomx = scanner.nextInt();
            System.out.println("���������򳤶�y");
            roomy = scanner.nextInt();
        }while(roomx*roomy<3&&(roomx<0||roomy<0));
        System.out.println("�������ɿ��:" + roomx + "����:" + roomy + "����");
        init(roomx, roomy);
        System.out.println("���ӵĳ�ʼλ��Ϊ" + monkey.getLocation().toString());
        System.out.println("���ӵĳ�ʼλ��Ϊ" + box.getLocation().toString());
        System.out.println("�㽶�ĳ�ʼλ��Ϊ" + banana.getLocation().toString());
        System.out.println("���Ӽ����ж���");
        System.out.println("--------------------------------------------------");
        try {
            TimeUnit.SECONDS.sleep(2);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        while (!canfinish()) {
            System.out.println("--------------------------------------------------");
            if (!monkey.isNeedbox()&&!monkey.getLocation().equals(banana.getLocation())) {//����û�з��ֹ������㽶��ֱ��Goto�㽶λ��
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
                //���ӷ��ֹ������㽶����Ҫ����
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
                //��Ҫ���ӵ�ʱ��Goto����λ��
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
                //������Pushbox
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
                //�������㽶�£�������Ҫ��������Climbbox
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
                //�����������ϣ��������㽶�£���Ҫץ�㽶Grasp
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
        System.out.println("���ӻ�����㽶");
    }
}

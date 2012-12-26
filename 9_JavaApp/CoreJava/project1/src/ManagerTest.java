/**
 * This program demostrates inheritance
 * @version 0.1 2012-12-26
 * @author tusion
 */

import java.util.*;

public class ManagerTest {

	public static void main(String[] args) {

		Employee Bob = new Employee("Bob David", 80000, 1987, 2, 15);
		/*
		 * Employee[] staff = new Employee[3]; staff[0] = Bob; staff[1] = new
		 * Employee("Steven Gerge", 90000, 1979, 12, 5 ); staff[2] = new
		 * Employee("Tusion Wonder", 89000, 1983, 4, 22 );
		 */
		ArrayList<Employee> staff = new ArrayList<Employee>();
		staff.add(Bob);
		staff.add(new Employee("Steven Gerge", 90000, 1979, 12, 5));
		staff.add(new Employee("Tusion Wonder", 89000, 1983, 4, 22));

		for (Employee e : staff)
			System.out.println("name=" + e.getName() + ", salary="
					+ e.getSalary() + ", hire day:" + e.getHireDate());

		System.out.println(Bob.getName() + Bob.getHireDate());
		
		System.out.println(staff.get(1).toString());

		Manager manager = new Manager("PengZhou", 19000, 1979, 1, 2);
		//Manager manager = (Manager) staff.get(2);
		manager.setBonus(5000);
		System.out.println(manager.toString());
		
		Employee tester = (Employee) manager;
		System.out.println( tester.toString());
	}

}

/*定义一个基本类用于演示类的基本操作*/
class Employee {
	public Employee(String s_name, double d_salary, int year, int month, int day) {
		name = s_name;
		salary = d_salary;
		GregorianCalendar calendar = new GregorianCalendar(year, month - 1, day);
		hireDay = calendar.getTime();
	}

	public String getName() {
		return name;
	}

	public double getSalary() {
		return salary;
	}

	public Date getHireDate() {
		return hireDay;
	}

	public void raiseSalary(double byPercent) {
		double raise = salary * byPercent / 100;
		salary += raise;
	}
	/*每个类最好有一个toString的方法，用于打印一些内部信息*/
	public String toString() {
		return getClass().getName() + "[name=" + name + " ,salary=" + salary
				+ " ,hire day:" + hireDay + " ]";
	}

	private String name;
	private double salary;
	private Date hireDay;
}

/*Employee的继承类，多了一个数据bonus */
class Manager extends Employee {
	public Manager(String s_name, double d_salary, int year, int month, int day) {
		super(s_name, d_salary, year, month, day);
		bonus = 0;
	}

	public double getSalary() {
		double baseSalary = super.getSalary();
		return (baseSalary + bonus);
	}

	public void setBonus(double b) {
		bonus = b;
	}

	public String toString() {
		return getClass().getName() + super.toString() + " ,bonus= " + bonus;
	}

	private double bonus;
}
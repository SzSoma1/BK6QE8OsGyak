package homework;

public class Homework {
	
	public static void main(String[] args)  {
		
		Book book1 = new Book();
		Book book2 = new Book();
		book1.setAuthor("J.K. Rowling");
		book1.setTitle("Harry Potter");
		
		book2.setAuthor("Csősz Péter");
		book2.setTitle("NORS38");
		
		// Test with invalid values
		book1.setYearOfPublication(2025);
		book1.setPrice(0);
		System.out.println(book1.toString());
		book1.increasePrice(-10);
		System.out.println(book1.toString());
		
		book2.setYearOfPublication(2010);
		book2.setPrice(1500);
		System.out.println(book2.toString());
		book2.increasePrice(20);
		System.out.println(book2.toString());
		
		// Test with valid values
		book1.setYearOfPublication(2008);
		book1.setPrice(3500);
		System.out.println(book1.toString());
		book1.increasePrice(10);
		System.out.println(book1.toString());
		
		book2.setYearOfPublication(2013);
		book2.setPrice(4500);
		System.out.println(book2.toString());
		book2.increasePrice(15);
		System.out.println(book2.toString());

	}
}

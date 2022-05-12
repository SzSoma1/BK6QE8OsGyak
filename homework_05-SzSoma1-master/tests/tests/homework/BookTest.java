package tests.homework;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.ValueSource;

import homework.Book;


public class BookTest{
	
	protected static final String author = "J.K. Rowling";
	protected static final String title = "Harry Potter";
	protected static final int yearOfPub = 2008;
	protected static final int price = 3500;
	
	protected Book createValidBook() {
		return new Book(author, title, yearOfPub, price);
	}
	
	@Test
	@DisplayName("A setPrice-nak az 1000 feletti értéket érintetlenül kell hagynia!")
	public void setPrice_Above999_ShouldNotBeChanged()
	{
		Book book = createValidBook();
		book.setPrice(price);

		assertEquals(price, book.getPrice());
	}
	
	@Test
	@DisplayName("Az increasePrice-nak pozitív értékre módosítania kell az árat!")
	public void increasePrice_ByAPositiveValue_ShouldChangePrice()
	{
		Book book = createValidBook();
		int originalPrice = 3500;
		book.setPrice(originalPrice);
		int expectedIncreasedPrice = 4025;
		book.increasePrice(15);

		assertEquals(expectedIncreasedPrice, book.getPrice());
	}
	
	@ParameterizedTest
	@ValueSource(ints = {0, -10})
	@DisplayName("Az increasePrice-nak nem pozitív értékre nem szabad módosítania az árat!")
	public void increasePrice_By0OrNegativeValue_ShouldNotChangePrice(int priceInc)
	{
		Book book = createValidBook();
		int originalPrice = 3500;
		book.setPrice(originalPrice);
		int expectedIncreasedPrice = book.getPrice();
		book.increasePrice(priceInc);

		assertEquals(expectedIncreasedPrice, book.getPrice());
	}
	
	@ParameterizedTest
	@CsvSource({"1004,1104", "1005,1106", "1006,1107"})
	@DisplayName("Az increasePrice-nak tört eredmény esetén kerekítenie kell a matematikai szabályoknak megfelelõen!")
	public void increasePrice_FractionalResult_ShouldBeRoundedAccordingToArithmeticRules(int originalPrice, int expectedPrice)
	{
		Book book = createValidBook();
		book.setPrice(originalPrice);
		book.increasePrice(10);

		assertEquals(expectedPrice, book.getPrice());
	}
	
	@ParameterizedTest
	@ValueSource(ints = {-1001, -1000, -999, 0, 999})
	@DisplayName("Az setPrice-nak az 1000 alatti értékeket 1000-re kell állítania")
	public void setPrice_Below1000_ShouldBeCorrectedTo1000(int price)
	{
		Book book = createValidBook();
		book.setPrice(price);
		assertEquals(1000, book.getPrice());
	}
	
	@Test
	@DisplayName("Az displayInfo kimenetének tartalmaznia kell a címet")
	public void displayInfo_ResultShouldContainTitle()
	{
		Book book = createValidBook();
		String result = book.displayInfo();
		assertTrue(result.contains(title),
				"A displayInfo által elõállított string nem tartalmazza az árat!");
	}
	
	@Test
	@DisplayName("Az displayInfo kimenetének tartalmaznia kell a szerzõt")
	public void displayInfo_ResultShouldContainAuthor()
	{
		Book book = createValidBook();
		String result = book.displayInfo();
		assertTrue(result.contains(author),
				"A displayInfo által elõállított string nem tartalmazza az árat!");
	}
	
	@Test
	@DisplayName("Az displayInfo kimenetének tartalmaznia kell a publikáció évét")
	public void displayInfo_ResultShouldContainYearOfPublication()
	{
		Book book = createValidBook();
		String result = book.displayInfo();
		assertTrue(result.contains(Integer.toString(yearOfPub)),
				"A displayInfo által elõállított string nem tartalmazza az árat!");
	}
	
	@Test
	@DisplayName("Az displayInfo kimenetének tartalmaznia kell az árat")
	public void displayInfo_ResultShouldContainPrice()
	{
		Book book = createValidBook();
		String result = book.displayInfo();
		assertTrue(result.contains(Integer.toString(price)),
				"A displayInfo által elõállított string nem tartalmazza az árat!");
	}
	
	@Test
	@DisplayName("A 2 paraméteres konstruktornak az árat 2500-ra kell állítania!")
	public void _2ParamConstructor_ShouldSetPriceTo2500()
	{
		Book book = new Book(author, title);
		assertEquals(2500, book.getPrice());
	}
	
	@Test
	@DisplayName("A 2 paraméteres konstruktornak a megjelenés évét a jelenlegi évre kell állítania!")
	public void _2ParamConstructor_ShouldSetPriceToYearOfPublicationToCurrentYear()
	{
		Book book = new Book(author, title);
		java.time.LocalDate currentDate = java.time.LocalDate.now();
		assertEquals(currentDate.getYear(), book.getYearOfPublication());
	}
	
	@Test
	@DisplayName("A toString metódus kimenetének meg kell egyeznie a displayInfo kimenetével!")
	public void toString_ShouldReturnTheSameAsDisplayInfo()
	{
		Book book = createValidBook();
		assertEquals(book.toString(), book.displayInfo());
	}
	
	@ParameterizedTest
	@CsvSource({"2000,2000,0", "2001,2000,1", "2000,2001,2"})
	@DisplayName("Az comparePublicationDate metódusnak 0-t kell adnia, ha a 2 évszám megegyezik, 1-et, ha az 1. nagyobb, 2-t, ha 2.!")
	public void comparePublicationDate_ShouldReturn0ForMatchingYears1Or2IfTheFirstOrSecondisGreater(int pubYearA, int pubYearB, int compResult)
	{
		Book bookA = createValidBook();
		bookA.setYearOfPublication(pubYearA);
		
		Book bookB = createValidBook();
		bookB.setYearOfPublication(pubYearB);

		assertEquals(compResult, Book.comparePublicationDate(bookA, bookB));
	}
}

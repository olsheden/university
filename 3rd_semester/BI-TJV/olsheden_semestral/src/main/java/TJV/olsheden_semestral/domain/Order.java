package TJV.olsheden_semestral.domain;

import javax.persistence.*;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Collection;
import java.util.List;
import java.util.Objects;
import java.util.Set;

@Entity
@Table(name = "order_table")
public class Order {

    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "order_generator")
    @SequenceGenerator (name = "order_generator", sequenceName = "Order_seq", allocationSize = 1)
    private Long id;

    private LocalDateTime date;

    private Long summa;

    @ElementCollection
    private List<String> product_type;

    private Long tips;

    @ManyToOne
    private Client client;




    @ManyToMany(fetch = FetchType.LAZY,
            cascade = {
                    CascadeType.PERSIST,
                    CascadeType.MERGE
            })
    @JoinTable(name = "orders_from_restaurants",
            joinColumns = @JoinColumn(name = "order_id"),
            inverseJoinColumns = @JoinColumn(name = "restaurant_id"))
    private Set<Restaurant> restaurants;


    public Order(Long id, LocalDateTime date, Long summa, List<String> product_type, Long tips, Client client, Set<Restaurant> restaurants) {
        this.id = id;
        this.date = date;
        this.summa = summa;
        this.product_type = product_type;
        this.tips = tips;
        this.client = client;
        this.restaurants = restaurants;
    }

    public Order() {

    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }


    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public Long getSumma() {
        return summa;
    }

    public void setSumma(Long summa) {
        this.summa = summa;
    }

    public List<String> getProduct_type() {
        return product_type;
    }

    public void setProduct_type(List<String> product_type) {
        this.product_type = product_type;
    }

    public Long getTips() {
        return tips;
    }

    public void setTips(Long tips) {
        this.tips = tips;
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public Set<Restaurant> getRestaurants() {
        return restaurants;
    }

    public void setRestaurants(Set<Restaurant> restaurants) {
        this.restaurants = restaurants;
    }

    public void addRestaurant(Restaurant restaurant){
        if(restaurants.contains(restaurant)) return;
        restaurants.add(restaurant);
    }

    public void deleteRestaurant(Restaurant restaurant){
        if(restaurants.contains(restaurant)){
            restaurants.remove(restaurant);
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Order order = (Order) o;
        return Objects.equals(id, order.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString() {
        return "Order{" +
                "id=" + id +
                ", date=" + date +
                ", summa=" + summa +
                ", product_type='" + product_type + '\'' +
                ", tips=" + tips +
                ", client=" + client +
                ", restaurants=" + restaurants +
                '}';
    }
}

package TJV.olsheden_semestral.dtos;

import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.domain.Restaurant;
import com.fasterxml.jackson.annotation.JsonView;
import org.springframework.stereotype.Component;

import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Collection;
import java.util.List;
import java.util.Set;

public class OrderDto {

    public Long id;

    public LocalDateTime date;

    public Long summa;

    public List<String> product_type;

    public Long tips;

    public Long clientId;

    public Collection<Long> restaurantsId;

    public OrderDto() {
    }

    public OrderDto(Long id, LocalDateTime date, Long summa, List<String> product_type, Long tips, Long clientId, Collection<Long> restaurantsId) {
        this.id = id;
        this.date = date;
        this.summa = summa;
        this.product_type = product_type;
        this.tips = tips;
        this.clientId = clientId;
        this.restaurantsId = restaurantsId;
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

    public Long getClientId() {
        return clientId;
    }

    public void setClientId(Long clientId) {
        this.clientId = clientId;
    }

    public Collection<Long> getRestaurantsId() {
        return restaurantsId;
    }

    public void setRestaurantsId(Collection<Long> restaurantsId) {
        this.restaurantsId = restaurantsId;
    }
}

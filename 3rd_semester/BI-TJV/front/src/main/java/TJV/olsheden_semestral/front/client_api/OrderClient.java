package TJV.olsheden_semestral.front.client_api;

import TJV.olsheden_semestral.front.domain.OrderDto;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.Entity;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import java.util.Arrays;
import java.util.Collection;
import java.util.Optional;

@Component
public class OrderClient {
    private WebTarget allOrderEndpoint;
    private WebTarget singleEndpointTemplate;
    private WebTarget singleOrderEndpoint;


    public OrderClient(@Value("${server.url}") String apiUrl) {
        var c = ClientBuilder.newClient();
        allOrderEndpoint = c.target(apiUrl + "/orders");
        singleEndpointTemplate = allOrderEndpoint.path("/{id}");
    }

    public OrderDto create(OrderDto e) {
        return allOrderEndpoint.request(MediaType.APPLICATION_JSON_TYPE)
                .post(Entity.entity(e, MediaType.APPLICATION_JSON_TYPE), OrderDto.class);
    }

    public Collection<OrderDto> readAll() {
        var res = allOrderEndpoint.request(MediaType.APPLICATION_JSON_TYPE)
                .get(OrderDto[].class);
        return Arrays.asList(res);
    }

    public Optional<OrderDto> readOne() {
        var response = singleOrderEndpoint.request(MediaType.APPLICATION_JSON_TYPE).get();
        if (response.getStatus() == 200)
            return Optional.of(response.readEntity(OrderDto.class));
        else if (response.getStatus() == 404) {
            return Optional.empty();
        } else
            throw new RuntimeException(response.getStatusInfo().getReasonPhrase());
    }

    public void setCurrentOrder(long id) {
        singleOrderEndpoint = singleEndpointTemplate.resolveTemplate("id", id);
    }

    public void updateOne(OrderDto e) {
        singleOrderEndpoint.request(MediaType.APPLICATION_JSON_TYPE).put(Entity.entity(e, MediaType.APPLICATION_JSON_TYPE));
    }

    public void deleteOne() {
        singleOrderEndpoint.request(MediaType.APPLICATION_JSON_TYPE).delete();
    }


    public Long countClientsWithAllProducts(String productType1, String productType2, String productType3){
        WebTarget countClientsWithAllProductsEndpoint = allOrderEndpoint.path("/count")
                .queryParam("productType1", productType1)
                .queryParam("productType2", productType2)
                .queryParam("productType3", productType3);
        return countClientsWithAllProductsEndpoint.request(MediaType.APPLICATION_JSON_TYPE).get(Long.class);
    }
}

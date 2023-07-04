package TJV.olsheden_semestral.front.client_api;


import TJV.olsheden_semestral.front.domain.RestaurantDto;
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
public class RestaurantClient {
    private WebTarget allRestaurantEndpoint;
    private WebTarget singleEndpointTemplate;
    private WebTarget singleRestaurantEndpoint;

    public RestaurantClient(@Value("${server.url}") String apiUrl) {
        var c = ClientBuilder.newClient();
        allRestaurantEndpoint = c.target(apiUrl + "/restaurants");
        singleEndpointTemplate = allRestaurantEndpoint.path("/{id}");
    }

    public RestaurantDto create(RestaurantDto e) {
        return allRestaurantEndpoint.request(MediaType.APPLICATION_JSON_TYPE)
                .post(Entity.entity(e, MediaType.APPLICATION_JSON_TYPE), RestaurantDto.class);
    }

    public Collection<RestaurantDto> readAll() {
        var res = allRestaurantEndpoint.request(MediaType.APPLICATION_JSON_TYPE)
                .get(RestaurantDto[].class);
        return Arrays.asList(res);
    }

    public Optional<RestaurantDto> readOne() {
        var response = singleRestaurantEndpoint.request(MediaType.APPLICATION_JSON_TYPE).get();
        if (response.getStatus() == 200)
            return Optional.of(response.readEntity(RestaurantDto.class));
        else if (response.getStatus() == 404) {
            return Optional.empty();
        } else
            throw new RuntimeException(response.getStatusInfo().getReasonPhrase());
    }

    public void setCurrentRestaurant(long id) {
        singleRestaurantEndpoint = singleEndpointTemplate.resolveTemplate("id", id);
    }


    public void updateOne(RestaurantDto e) {
        singleRestaurantEndpoint.request(MediaType.APPLICATION_JSON_TYPE).put(Entity.entity(e, MediaType.APPLICATION_JSON_TYPE));
    }

    public void deleteOne() {
        singleRestaurantEndpoint.request(MediaType.APPLICATION_JSON_TYPE).delete();
    }
}
